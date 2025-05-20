import unittest
from http import HTTPStatus

from tests.send_func import requests, send_post, send_delete


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
