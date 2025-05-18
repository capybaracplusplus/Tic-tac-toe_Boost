import requests

url = "http://127.0.0.1:8080/game/create"
data = {
    "password": "mysecretpassword122332133",
    "aboba": "asd3213123s"
}

with requests.Session() as session:
    response = session.post(url, json=data)
    print("Status code:", response.status_code)
    print("Response body:", response.text)

print("easy")
