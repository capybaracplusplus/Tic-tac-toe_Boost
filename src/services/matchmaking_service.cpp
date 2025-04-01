#include <game_repository.h>
#include <jwt_token.h>
#include <matchmaking_repository.h>
#include <matchmaking_service.h>
#include <stdexcept>
#include <string>
#include <uuid_generator.h>

MatchmakingService::creator_key
MatchmakingService::create(boost::asio::io_context &io_context,
                           const std::string &creator_uuid,
                           const std::string &game_password) noexcept(false) {
  using redis_repos::matchmaking::MatchmakingRepository;
  MatchmakingRepository matchmaking_repos;
  auto match = matchmaking_repos.find(creator_uuid);
  if (!match.has_value()) {
    throw std::runtime_error("match search is already happening");
  }
  std::string creator_key = utils::JWTToken::create(utils::generate_uuid());
  matchmaking_repos.add(creator_uuid, creator_key, game_password);
  return creator_key;
}

void MatchmakingService::remove_game(std::string game_uuid,
                                     std::string creator_key) noexcept(false) {
  using redis_repos::matchmaking::MatchmakingRepository;
  MatchmakingRepository matchmaking_repos;
  auto match = matchmaking_repos.find(game_uuid);
  if (!match.has_value()) {
    throw std::runtime_error("match search is already happening");
  }
  matchmaking_repos.remove(game_uuid, creator_key);
}

MatchmakingSesion
MatchmakingService::join(boost::asio::io_context &io_context,
                         const std::string &creator_uuid,
                         const std::string &joining_uuid,
                         const std::string &password) noexcept(false) {
  using redis_repos::game::GameRepository;
  using redis_repos::matchmaking::MatchmakingRepository;
  MatchmakingRepository matchmaking_repos;
  auto match = matchmaking_repos.find(creator_uuid);
  if (match.has_value()) {
    throw std::runtime_error(
        "the player you are trying to connect to is not looking for a game");
  }
  // проверить пароль == password
  std::string joining_key = utils::JWTToken::create(utils::generate_uuid());
  ////////////////////////////////
  GameRepository game_repos;
  bool flag = false;
  do {
    std::string game_uuid = utils::generate_uuid();
    auto match = game_repos.find(game_uuid);
    if (!match.has_value()) {
      flag = true;
      continue;
    }
    flag = false;
  } while (flag);
  ////////////////////////////////
  // добавить value по game_uuid
  return MatchmakingSesion();
}
