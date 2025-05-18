import requests

BASE_URL = "http://127.0.0.1:8080"
GREEN = "\033[92m"
RED = "\033[91m"
RESET = "\033[0m"

def send_post(endpoint: str, data: dict) -> requests.Response:
    with requests.Session() as session:
        return session.post(f"{BASE_URL}{endpoint}", json=data)

def send_get(endpoint: str) -> requests.Response:
    with requests.Session() as session:
        return session.get(f"{BASE_URL}{endpoint}")