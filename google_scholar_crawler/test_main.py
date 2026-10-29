import json
import os
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

import main


class CitationCrawlerTests(unittest.TestCase):
    def setUp(self):
        self.directory = tempfile.TemporaryDirectory()
        self.addCleanup(self.directory.cleanup)
        self.root = Path(self.directory.name)
        self.config = self.root / "_config.yml"
        self.config.write_text(
            'author:\n  googlescholar: "https://scholar.google.com/citations?user=test-author"\n',
            encoding="utf-8",
        )

    @patch.dict(os.environ, {"GOOGLE_SCHOLAR_ID": ""})
    def test_missing_secret_uses_public_profile(self):
        self.assertEqual(main.scholar_id(self.config), "test-author")

    @patch.dict(os.environ, {"GOOGLE_SCHOLAR_ID": "test-author"})
    def test_matching_secret_is_supported(self):
        self.assertEqual(main.scholar_id(self.config), "test-author")

    @patch.dict(os.environ, {"GOOGLE_SCHOLAR_ID": "wrong-author"})
    def test_stale_secret_fails_instead_of_publishing_another_author(self):
        with self.assertRaisesRegex(ValueError, "does not match"):
            main.scholar_id(self.config)

    def test_duplicate_profile_parameters_fail(self):
        self.config.write_text(
            'author:\n  googlescholar: "https://scholar.google.com/citations?user=SCHOLAR_ID&user=test-author"\n',
            encoding="utf-8",
        )
        with self.assertRaisesRegex(ValueError, "one valid user"):
            main.scholar_id(self.config)

    @patch.object(main, "scholarly")
    def test_incomplete_fetch_does_not_overwrite_last_good_data(self, scholarly):
        previous = {"scholar_id": "test-author", "citedby": 10, "publications": {}}
        main.write_results(previous, self.root)
        scholarly.search_author_id.return_value = {"scholar_id": "test-author"}
        with self.assertRaisesRegex(ValueError, "valid citation count"):
            author = main.fetch_author("test-author")
            main.write_results(author, self.root)
        self.assertEqual(json.loads((self.root / "gs_data.json").read_text()), previous)

    @patch.object(main, "scholarly")
    def test_zero_citations_and_publication_keys_are_preserved(self, scholarly):
        scholarly.search_author_id.return_value = {
            "scholar_id": "test-author",
            "name": "研究者",
            "citedby": 0,
            "publications": [{"author_pub_id": "test-author:paper", "num_citations": 0}],
        }
        author = main.fetch_author("test-author")
        main.write_results(author, self.root)
        data = json.loads((self.root / "gs_data.json").read_text())
        self.assertEqual(data["publications"]["test-author:paper"]["num_citations"], 0)
        self.assertEqual(data["name"], "研究者")
        self.assertEqual(json.loads((self.root / "gs_data_shieldsio.json").read_text())["message"], "0")


if __name__ == "__main__":
    unittest.main()
