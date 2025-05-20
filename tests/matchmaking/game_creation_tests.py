import unittest
from http import HTTPStatus

from tests.send_func import requests, send_post


class GameCreationTests(unittest.TestCase):
    def setUp(self):
        self.password = {"password": "Password123456789"}

    def test_create_open_game(self):
        sessions = requests.Session()

        res_1 = send_post(sessions, "/game/create", {})
        self.assertEqual(res_1.status_code, HTTPStatus.CREATED)
        self.assertTrue(res_1.text)

        res_2 = send_post(sessions, "/game/create", {})
        self.assertEqual(res_2.status_code, HTTPStatus.CONFLICT)
        self.assertTrue(res_2.text)

        res_3 = send_post(sessions, "/game/create", {})
        self.assertEqual(res_3.status_code, HTTPStatus.CONFLICT)
        self.assertTrue(res_3.text)

        sessions.close()

    def test_create_close_game(self):
        sessions = requests.Session()

        res_1 = send_post(sessions, "/game/create", self.password)
        self.assertEqual(res_1.status_code, HTTPStatus.CREATED)
        self.assertTrue(res_1.text)

        res_2 = send_post(sessions, "/game/create", self.password)
        self.assertEqual(res_2.status_code, HTTPStatus.CONFLICT)
        self.assertTrue(res_2.text)

        res_3 = send_post(sessions, "/game/create", self.password)
        self.assertEqual(res_3.status_code, HTTPStatus.CONFLICT)
        self.assertTrue(res_3.text)

        res_4 = send_post(sessions, "/game/create", self.password)
        self.assertEqual(res_4.status_code, HTTPStatus.CONFLICT)
        self.assertTrue(res_4.text)

        sessions.close()
