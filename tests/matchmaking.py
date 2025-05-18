import sys
from send_func import *

def  create_game_open():
    data = {
        "password": "Password123456789",
    }
    res = send_post("/game/create",data)
    res.raise_for_status()
    if not res.text:
        raise ValueError("Response body is empty")
    print(f"{GREEN}Func create_game_open is done{RESET}")

def  create_game_close():
    data = {
        "password": "Password123456789",
    }
    res = send_post("/game/create",data)
    res.raise_for_status()
    if not res.text:
        raise ValueError("Response body is empty")
    print(f"{GREEN}Func create_game_close is done{RESET}")


def main():
    try:
        create_game_open()
        create_game_close()
    except Exception as e:
        print(f"{RED}Error: {e}{RESET}")
        sys.exit(1)

if __name__ == "__main__":
    main()