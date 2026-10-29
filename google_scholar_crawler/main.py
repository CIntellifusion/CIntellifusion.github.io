import json
import os
from datetime import datetime, timezone
from pathlib import Path
from urllib.parse import parse_qs, urlparse

import yaml
from scholarly import scholarly


ROOT = Path(__file__).resolve().parent.parent


def scholar_id(config_path=ROOT / "_config.yml"):
    """Use the existing secret, or the public profile already configured on the site."""
    with config_path.open(encoding="utf-8") as config_file:
        config = yaml.safe_load(config_file)
    profile_url = config.get("author", {}).get("googlescholar", "")
    profile_ids = parse_qs(urlparse(profile_url).query).get("user", [])
    if len(profile_ids) != 1 or profile_ids[0] == "SCHOLAR_ID":
        raise ValueError("Set one valid user parameter in author.googlescholar in _config.yml.")
    configured_id = profile_ids[0]
    override = os.environ.get("GOOGLE_SCHOLAR_ID", "").strip()
    if override and override != configured_id:
        raise ValueError("GOOGLE_SCHOLAR_ID does not match author.googlescholar; update or remove the stale secret.")
    return override or configured_id


def fetch_author(author_id):
    scholarly.set_timeout(30)
    scholarly.set_retries(2)
    author = scholarly.search_author_id(author_id)
    scholarly.fill(author, sections=["basics", "indices", "counts", "publications"])
    if author.get("scholar_id") != author_id:
        raise ValueError("Google Scholar returned a different author; existing data was not changed.")
    if type(author.get("citedby")) is not int or author["citedby"] < 0:
        raise ValueError("Google Scholar did not return a valid citation count.")
    if not isinstance(author.get("publications"), list):
        raise ValueError("Google Scholar did not return a publication list.")
    author["publications"] = {paper["author_pub_id"]: paper for paper in author["publications"]}
    author["updated"] = datetime.now(timezone.utc).isoformat()
    return author


def write_results(author, output_dir=Path(__file__).resolve().parent / "results"):
    output_dir.mkdir(parents=True, exist_ok=True)
    shields_data = {
        "schemaVersion": 1,
        "label": "citations",
        "message": str(author["citedby"]),
    }
    for filename, data in (("gs_data.json", author), ("gs_data_shieldsio.json", shields_data)):
        output = output_dir / filename
        temporary = output.with_suffix(".json.tmp")
        temporary.write_text(json.dumps(data, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
        temporary.replace(output)


def main():
    author = fetch_author(scholar_id())
    write_results(author)
    print(f"Updated {len(author['publications'])} publications at {author['updated']}.")


if __name__ == "__main__":
    main()
