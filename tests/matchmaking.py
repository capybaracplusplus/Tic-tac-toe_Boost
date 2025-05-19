import unittest
from send_func import send_post

class GameCreationTests(unittest.TestCase):
    def setUp(self):
        self.password = {"password": "Password123456789"}

    def test_create_game_open(self):
        res = send_post("/game/create", self.password)
        self.assertEqual(res.status_code, 200)
        self.assertTrue(res.text)

    def test_create_game_close(self):
        res = send_post("/game/create", self.password)
        self.assertEqual(res.status_code, 200)
        self.assertTrue(res.text)

if __name__ == '__main__':
    unittest.main()
