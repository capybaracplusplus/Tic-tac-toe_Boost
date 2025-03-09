#ifndef SERVICE_H
#define SERVICE_H

#include <string>

class Service {
public:
    static void aboba();

    static std::string get_id();

    static std::string create_game(std::string id);

    static std::string join_game(std::string id);

    static std::string remove_game(std::string id);

    static std::string make_a_move(std::string id);
};


#endif //SERVICE_H
