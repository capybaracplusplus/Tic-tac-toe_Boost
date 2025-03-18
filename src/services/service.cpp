#include <service.h>
#include <redis_repository.h>
#include <uuid_generator.h>
#include <jwt_token.h>

GameSession service::create_game(bool is_open, std::string game_password) {
    std::string game_id = utils::generate_uuid();

    std::string key_1 = utils::JWTToken().create();
    std::string key_2 = utils::JWTToken().create();

    // send Redis req

    //repos::Session().create_session();
}
