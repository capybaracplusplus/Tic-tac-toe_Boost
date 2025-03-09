#ifndef SERVICE_H
#define SERVICE_H

#include <string>

struct GameSession {
    std::string game_id;
    std::string key;
};

/*
    REDIS
    key:value

game_session

UUID_game: {
                key_1
                key_2
                password
                game_value
           }
---------------------------------------------

 */

class service {
public:
    static GameSession create_game(bool is_open = true, std::string game_password = "");

    static GameSession join_game(std::string game_id, std::string game_password = "");

    static std::string remove_game(std::string id);

    static std::string make_a_move(std::string id);
};


#endif //SERVICE_H
