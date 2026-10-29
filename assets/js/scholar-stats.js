(async function () {
  "use strict";

  const script = document.currentScript;
  const totalCitation = document.getElementById("total_cit");
  const citationElements = document.querySelectorAll(".show_paper_citations");

  if (!totalCitation && citationElements.length === 0) return;

  const urls = [script.dataset.primaryUrl, script.dataset.fallbackUrl].filter(Boolean);
  const isCitationCount = value => Number.isInteger(value) && value >= 0;

  async function fetchStats(url) {
    const controller = new AbortController();
    const timeout = setTimeout(() => controller.abort(), 8000);

    try {
      const response = await fetch(url, { signal: controller.signal });
      if (!response.ok) throw new Error("Citation request failed: " + response.status);

      const data = await response.json();
      if (!data || !isCitationCount(data.citedby) || !data.publications ||
          typeof data.publications !== "object" || Array.isArray(data.publications)) {
        throw new Error("Invalid citation data");
      }
      return data;
    } finally {
      clearTimeout(timeout);
    }
  }

  for (const url of urls) {
    try {
      const data = await fetchStats(url);

      if (totalCitation) totalCitation.textContent = String(data.citedby);

      citationElements.forEach(element => {
        const paperId = element.getAttribute("data");
        const publication = Object.prototype.hasOwnProperty.call(data.publications, paperId)
          ? data.publications[paperId] : null;
        if (publication && isCitationCount(publication.num_citations)) {
          element.textContent = "| Citations: " + publication.num_citations;
        }
      });
      return;
    } catch (error) {
      // Try the other host if this one is unavailable, slow, or has invalid JSON.
    }
  }

  // Leave unavailable counts blank instead of displaying a misleading zero.
  console.warn("Google Scholar citation data is unavailable; counts were not updated.");
})();
