#include <nlohmann/json.hpp>
#include <repositories/game_repository.h>
#include <repositories/matchmaking_repository.h>
#include <services/matchmaking_service.h>
#include <stdexcept>
#include <string>
#include <utils/jwt_token.h>
#include <utils/uuid_generator.h>

void MatchmakingService::create(
    boost::asio::io_context &io_context, const std::string &creator_uuid,
    const std::string &game_password) noexcept(false) {
  std::optional<std::string> match;
  io_context.post([&match, creator_uuid, game_password]() {
    using redis_repos::matchmaking::MatchmakingRepository;
    MatchmakingRepository matchmaking_repos;
    match = matchmaking_repos.find(creator_uuid);
    if (match.has_value()) {
      throw std::runtime_error("match search is already happening");
    }
    matchmaking_repos.add(creator_uuid, game_password);
  });
}

void MatchmakingService::remove_game(boost::asio::io_context &io_context,
                                     std::string game_uuid) noexcept(false) {
  using redis_repos::matchmaking::MatchmakingRepository;
  MatchmakingRepository matchmaking_repos;
  auto match = matchmaking_repos.find(game_uuid);
  if (!match.has_value()) {
    throw std::runtime_error("match search is already happening");
  }
  matchmaking_repos.remove(game_uuid);
}

MatchmakingSesion
MatchmakingService::join(boost::asio::io_context &io_context,
                         const std::string &creator_uuid,
                         const std::string &joining_uuid,
                         const std::string &password) noexcept(false) {
  using redis_repos::game::GameRepository;
  using redis_repos::matchmaking::MatchmakingRepository;
  MatchmakingRepository matchmaking_repos;

  auto val = matchmaking_repos.find(creator_uuid);
  if (!val.has_value()) {
    throw std::runtime_error(
        "the player you are trying to connect to is not looking for a game");
  }

  nlohmann::json json_object = nlohmann::json::parse(val.value());
  std::string game_password = json_object["password"];
  if (password != game_password) {
    throw std::runtime_error(
        "The password for the game you are trying to connect to is incorrect");
  }

  GameRepository game_repos;
  std::string game_uuid;
  bool flag = false;

  do {
    game_uuid = utils::generate_uuid();
  } while (game_repos.find(game_uuid).has_value());

  MatchmakingSesion new_game_session = {.game_uuid = game_uuid,
                                        .creator_uuid = creator_uuid,
                                        .joining_uuid = joining_uuid};

  game_repos.add(new_game_session);
  return new_game_session;
}
