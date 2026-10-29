const assert = require("node:assert/strict");
const fs = require("node:fs");
const path = require("node:path");
const test = require("node:test");
const vm = require("node:vm");

const source = fs.readFileSync(
  path.join(__dirname, "../assets/js/scholar-stats.js"), "utf8"
);
const cdnUrl = "https://cdn.jsdelivr.net/gh/example/site@google-scholar-stats/gs_data.json";
const rawUrl = "https://raw.githubusercontent.com/example/site/google-scholar-stats/gs_data.json";

function paper(id) {
  return {
    textContent: "",
    getAttribute(name) {
      assert.equal(name, "data");
      return id;
    }
  };
}

function response(data) {
  return { ok: true, status: 200, json: async () => data };
}

function run({ total = null, papers = [], replies = [], primary = cdnUrl, fallback = rawUrl } = {}) {
  const requests = [];
  const warnings = [];
  const timers = new Map();
  let timerId = 0;
  const context = {
    document: {
      currentScript: { dataset: { primaryUrl: primary, fallbackUrl: fallback } },
      getElementById(id) {
        assert.equal(id, "total_cit");
        return total;
      },
      querySelectorAll(selector) {
        assert.equal(selector, ".show_paper_citations");
        return papers;
      }
    },
    AbortController,
    fetch(url, options) {
      const reply = replies[requests.length];
      requests.push({ url, signal: options.signal });
      if (!reply) return Promise.reject(new Error("Unexpected request: " + url));
      return Promise.resolve().then(() => reply(url, options));
    },
    setTimeout(callback, delay) {
      const id = ++timerId;
      timers.set(id, { callback, delay });
      return id;
    },
    clearTimeout(id) { timers.delete(id); },
    console: { warn(message) { warnings.push(message); } }
  };
  const done = vm.runInNewContext(source, context, { filename: "scholar-stats.js" });
  return { done, requests, warnings, timers };
}

test("updates paper citations without a total-citation element", async () => {
  const publication = paper("author:paper");
  const result = run({
    papers: [publication],
    replies: [() => response({ citedby: 42, publications: { "author:paper": { num_citations: 12 } } })]
  });
  await result.done;
  assert.equal(publication.textContent, "| Citations: 12");
  assert.deepEqual(result.requests.map(request => request.url), [cdnUrl]);
  assert.deepEqual(result.warnings, []);
  assert.equal(result.timers.size, 0);
});

test("displays genuine zero counts for both total and paper", async () => {
  const total = { textContent: "" };
  const publication = paper("new-paper");
  const result = run({
    total,
    papers: [publication],
    replies: [() => response({ citedby: 0, publications: { "new-paper": { num_citations: 0 } } })]
  });
  await result.done;
  assert.equal(total.textContent, "0");
  assert.equal(publication.textContent, "| Citations: 0");
});

test("missing and invalid paper counts stay blank without blocking a valid paper", async () => {
  const ids = ["missing", "null-record", "missing-count", "negative", "fraction", "string", "null-count", "valid"];
  const papers = ids.map(paper);
  const result = run({
    papers,
    replies: [() => response({
      citedby: 15,
      publications: {
        "null-record": null,
        "missing-count": {},
        negative: { num_citations: -1 },
        fraction: { num_citations: 1.5 },
        string: { num_citations: "7" },
        "null-count": { num_citations: null },
        valid: { num_citations: 15 }
      }
    })]
  });
  await result.done;
  assert.deepEqual(papers.slice(0, -1).map(element => element.textContent), Array(7).fill(""));
  assert.equal(papers.at(-1).textContent, "| Citations: 15");
  assert.deepEqual(result.warnings, []);
});

test("falls back when the primary host cannot provide usable data", async t => {
  const failures = {
    "HTTP 404": () => ({ ok: false, status: 404, json: async () => { throw new Error("Must not parse a failed response"); } }),
    "network failure": () => { throw new TypeError("Failed to fetch"); },
    "invalid JSON": () => ({ ok: true, status: 200, json: async () => { throw new SyntaxError("Invalid JSON"); } }),
    "null payload": () => response(null),
    "missing total": () => response({ publications: {} }),
    "invalid total": () => response({ citedby: -1, publications: {} }),
    "missing publications": () => response({ citedby: 10 }),
    "array publications": () => response({ citedby: 10, publications: [] })
  };
  for (const [name, firstReply] of Object.entries(failures)) {
    await t.test(name, async () => {
      const total = { textContent: "" };
      const result = run({
        total,
        replies: [firstReply, () => response({ citedby: 27, publications: {} })]
      });
      await result.done;
      assert.deepEqual(result.requests.map(request => request.url), [cdnUrl, rawUrl]);
      assert.equal(total.textContent, "27");
      assert.deepEqual(result.warnings, []);
      assert.equal(result.timers.size, 0);
    });
  }
});

test("two unavailable hosts leave counts blank and emit one warning", async () => {
  const total = { textContent: "" };
  const publication = paper("paper");
  const result = run({
    total,
    papers: [publication],
    replies: [
      () => ({ ok: false, status: 404 }),
      () => { throw new TypeError("Network unavailable"); }
    ]
  });
  await result.done;
  assert.deepEqual(result.requests.map(request => request.url), [cdnUrl, rawUrl]);
  assert.equal(total.textContent, "");
  assert.equal(publication.textContent, "");
  assert.equal(result.warnings.length, 1);
  assert.match(result.warnings[0], /unavailable/i);
  assert.equal(result.timers.size, 0);
});

test("a timed-out request is aborted and advances to the fallback host", async () => {
  const total = { textContent: "" };
  const result = run({
    total,
    replies: [
      (_url, { signal }) => new Promise((resolve, reject) => {
        signal.addEventListener("abort", () => reject(new Error("Request aborted")), { once: true });
      }),
      () => response({ citedby: 9, publications: {} })
    ]
  });
  // Let the request attach its abort listener; advance the fake timer without a real wait.
  await Promise.resolve();
  assert.equal(result.timers.size, 1);
  const timer = [...result.timers.values()][0];
  assert.ok(timer.delay > 0 && timer.delay <= 10000);
  timer.callback();
  await result.done;
  assert.equal(result.requests[0].signal.aborted, true);
  assert.deepEqual(result.requests.map(request => request.url), [cdnUrl, rawUrl]);
  assert.equal(total.textContent, "9");
  assert.deepEqual(result.warnings, []);
  assert.equal(result.timers.size, 0);
});

test("does not fetch when the page has no citation targets", async () => {
  const result = run();
  await result.done;
  assert.deepEqual(result.requests, []);
  assert.deepEqual(result.warnings, []);
  assert.equal(result.timers.size, 0);
});

test("honors either configured host order", async t => {
  for (const [primary, fallback] of [[cdnUrl, rawUrl], [rawUrl, cdnUrl]]) {
    await t.test(primary === cdnUrl ? "CDN first" : "raw GitHub first", async () => {
      const total = { textContent: "" };
      const result = run({
        total,
        primary,
        fallback,
        replies: [() => ({ ok: false, status: 503 }), () => response({ citedby: 3, publications: {} })]
      });
      await result.done;
      assert.deepEqual(result.requests.map(request => request.url), [primary, fallback]);
      assert.equal(total.textContent, "3");
    });
  }
});
