#include "matchmaking_service.h"
#include <jwt_token.h>
#include <uuid_generator.h>

MatchmakingService::creator_key
MatchmakingService::create(boost::asio::io_context &io_context,
                           const std::string &creator_uuid,
                           const std::string &game_password) noexcept(false) {
  // game_uuid будет uuid
  // запрос в редис на проверку что нету uuid
  // если есть то кидаю исключение
  std::string creator_key = utils::JWTToken::create(utils::generate_uuid());
  // запрос в редис с созданием
  return creator_key;
}

void MatchmakingService::remove_game(std::string game_uuid,
                                     std::string creator_key) {
  // запрос в редис на проверку что есть такая игра и что там такой же
  // creator_key запрос на удаление игры из редиса
}

MatchmakingSesion
MatchmakingService::join(boost::asio::io_context &io_context,
                         const std::string &creator_uuid,
                         const std::string &joining_uuid,
                         const std::string &password) noexcept(false) {
  // сгенерить game_uuid
  // запрос на проверку что нету игры с таким game_uuid
  // ...?
  return MatchmakingSesion();
}
