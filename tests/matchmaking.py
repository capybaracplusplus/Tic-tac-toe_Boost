import unittest
from send_func import requests, send_post, send_delete
from http import HTTPStatus


class GameCreationTests(unittest.TestCase):
    def setUp(self):
        self.password = {"password": "Password123456789"}

    def test_create_open_game(self):
        sessions = requests.Session()
        res = send_post(sessions, "/game/create", {})
        self.assertEqual(res.status_code, HTTPStatus.CREATED)
        self.assertTrue(res.text)

    def test_create_close_game(self):
        sessions = requests.Session()
        res = send_post(sessions, "/game/create", self.password)
        self.assertEqual(res.status_code, HTTPStatus.CREATED)
        self.assertTrue(res.text)


class GameRemovalTests(unittest.TestCase):
    def setUp(self):
        self.password = {"password": "Password123456789"}

    def test_delete_open_game(self):
        sessions = requests.Session()
        res_create = send_post(sessions, "/game/create", {})
        self.assertEqual(res_create.status_code, HTTPStatus.CREATED)
        data = res_create.json()
        game_id = data["game_id"]
        res_delete = send_delete(sessions, "/game/remove")
        self.assertEqual(res_delete.status_code, HTTPStatus.OK)
        res_create = send_post(sessions, "/game/create", {})
        self.assertEqual(res_create.status_code, HTTPStatus.CREATED)


def test_delete_close_game(self):
    sessions = requests.Session()
    res_create = send_post(sessions, "/game/create", self.password)
    self.assertEqual(res_create.status_code, HTTPStatus.CREATED)
    data = res_create.json()
    game_id = data["game_id"]
    res_delete = send_delete(sessions, "/game/remove")
    self.assertEqual(res_delete.status_code, HTTPStatus.OK)
    res_create = send_post(sessions, "/game/create", {})
    self.assertEqual(res_create.status_code, HTTPStatus.CREATED)


class GameJoinTests(unittest.TestCase):
    def setUp(self):
        self.password = {"password": "Password123456789"}

    def test_join_open_game(self):
        sessions = requests.Session()
        res_create = send_post(sessions, "/game/create", {})
        self.assertEqual(res_create.status_code, HTTPStatus.CREATED)
        data = res_create.json()
        game_id = data["game_id"]
        session2 = requests.Session()
        res_join = send_post(session2, "/game/join", {"game_id": game_id})
        self.assertEqual(res_join.status_code, HTTPStatus.OK)
        self.assertTrue(res_join.text)

    def test_join_close_game(self):
        sessions = requests.Session()
        res_create = send_post(sessions, "/game/create", self.password)
        self.assertEqual(res_create.status_code, HTTPStatus.CREATED)
        data = res_create.json()
        game_id = data["game_id"]
        session2 = requests.Session()
        join_data = {"game_id": game_id, **self.password}
        res_join = send_post(session2, "/game/join", join_data)
        self.assertEqual(res_join.status_code, HTTPStatus.OK)
        self.assertTrue(res_join.text)


if __name__ == '__main__':
    unittest.main()
