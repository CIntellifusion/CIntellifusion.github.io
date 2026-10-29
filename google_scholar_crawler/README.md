# Citation data

The homepage no longer loads or displays citation counts. This optional crawler
is retained for manual JSON exports; automatic workflow triggers are disabled.

The crawler reads the Google Scholar profile in `author.googlescholar` in
`_config.yml`. The optional `GOOGLE_SCHOLAR_ID` environment variable / Actions
secret is still supported, but it must match that profile. Remove or update a
stale secret instead of publishing another author's counts.

## First run on GitHub

1. Ensure the workflow is present on the default branch.
2. Open the repository's **Actions → Get Citation Data** workflow. Forked
   repositories may have this workflow disabled; click **Enable workflow** first.
3. Click **Run workflow**, select `main`, and start the run.
4. Check that both **Fetch citation data** and **Publish citation data** succeed.
   A successful run creates the `google-scholar-stats` branch if it is missing.
5. Check the exported `gs_data.json` on that branch. The homepage does not read it.

The workflow runs only when manually dispatched. It requests `contents: write`
for its repository token; repository / organization policies must permit that access.

Publishing commits only the two JSON outputs to `google-scholar-stats`, preserving
existing branch history and unrelated files. It never force-pushes. A failed
fetch or validation stops the workflow before publishing, leaving the last
successful data intact.

## Local checks

Use Python 3.11 in a virtual environment, from the repository root:

```bash
python3.11 -m venv google_scholar_crawler/.venv
. google_scholar_crawler/.venv/bin/activate
python -m pip install -r google_scholar_crawler/requirements.txt
python -m unittest discover -s google_scholar_crawler -p 'test_*.py'
python google_scholar_crawler/main.py
```

The tests do not request live Scholar data. The final command fetches live data
and writes `google_scholar_crawler/results/gs_data.json` and
`gs_data_shieldsio.json`; it does not push anything. Running `python main.py`
inside the crawler directory is also supported.

Google Scholar may rate-limit or block automated requests. Request retries and
the Actions job are bounded; inspect the failed run and retry later rather than
replacing real counts with empty data.
