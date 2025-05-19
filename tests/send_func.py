import requests

BASE_URL = "http://127.0.0.1:8080"


def send_post(session, endpoint: str, data: dict) -> requests.Response:
    return session.post(f"{BASE_URL}{endpoint}", json=data)


def send_get(session, endpoint: str) -> requests.Response:
    return session.get(f"{BASE_URL}{endpoint}")


def send_delete(session, endpoint: str) -> requests.Response:
    return session.delete(f"{BASE_URL}{endpoint}")
