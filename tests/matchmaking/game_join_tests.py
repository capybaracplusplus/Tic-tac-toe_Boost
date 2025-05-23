import unittest
from http import HTTPStatus

from tests.send_func import requests, send_post


class GameJoinTests(unittest.TestCase):
    def setUp(self):
        self.password = {"password": "Password123456789"}

    def test_join_open_game(self):
        sessions = requests.Session()

        res_create = send_post(sessions, "/game/create", {})
        self.assertEqual(res_create.status_code, HTTPStatus.CREATED)

        data = res_create.json()
        self.assertIn("game_id", data)
        game_id = data["game_id"]

        session2 = requests.Session()

        res_join = send_post(session2, "/game/join", {"game_id": game_id})
        self.assertEqual(res_join.status_code, HTTPStatus.CREATED)
        self.assertTrue(res_join.text)
        self.assertEqual(res_join.headers["Content-Type"], "application/json")
        join_data = res_join.json()
        self.assertIn("game_id", join_data)
        self.assertIsInstance(join_data["game_id"], str)
        self.assertTrue(join_data["game_id"])

        sessions.close()

    def test_join_close_game(self):
        sessions = requests.Session()

        res_create = send_post(sessions, "/game/create", self.password)
        self.assertEqual(res_create.status_code, HTTPStatus.CREATED)

        data = res_create.json()
        self.assertIn("game_id", data)
        game_id = data["game_id"]
        join_data = {"game_id": game_id, **self.password}

        session2 = requests.Session()

        res_join = send_post(session2, "/game/join", join_data)
        self.assertEqual(res_join.status_code, HTTPStatus.CREATED)
        self.assertTrue(res_join.text)
        self.assertEqual(res_join.headers["Content-Type"], "application/json")
        join_data = res_join.json()
        self.assertIn("game_id", join_data)
        self.assertIsInstance(join_data["game_id"], str)
        self.assertTrue(join_data["game_id"])
        sessions.close()
