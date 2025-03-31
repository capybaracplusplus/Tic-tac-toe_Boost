#ifndef MATCHMAKING_SERVICE_H
#define MATCHMAKING_SERVICE_H

#include<boost/asio/io_service.hpp>

struct MatchmakingSesion {
    // key to check that the player has access to this game by uuid
    std::string game_uuid;
    std::string creator_uuid;
    std::string creator_key;
    std::string joining_uuid;
    std::string joining_key;
};

class MatchmakingService {
public:
    using creator_key = std::string;

public:
    static creator_key create(boost::asio::io_context &io_context, const std::string &creator_uuid,
                              const std::string &game_password) noexcept(false);

    static void remove_game(std::string game_uuid, std::string creator_key);


    static MatchmakingSesion join(boost::asio::io_context &io_context, const std::string &creator_uuid,
                                  const std::string &joining_uuid, const std::string &password) noexcept(false);
};

#endif //MATCHMAKING_SERVICE_H
