#include <jwt_token.h>
#include <matchmaking_repository.h>
#include <matchmaking_service.h>
#include <uuid_generator.h>

MatchmakingService::creator_key
MatchmakingService::create(boost::asio::io_context &io_context,
                           const std::string &creator_uuid,
                           const std::string &game_password) noexcept(false) {
  using redis_repos::matchmaking::MatchmakingRepository;
  MatchmakingRepository repo;
  auto match = repo.find(creator_uuid);
  if (!match.has_value()) {
    throw std::runtime_error("match search is already happening");
  }
  std::string creator_key = utils::JWTToken::create(utils::generate_uuid());
  repo.add(creator_uuid, creator_key, game_password);
  return creator_key;
}

void MatchmakingService::remove_game(std::string game_uuid,
                                     std::string creator_key) noexcept(false) {
  using redis_repos::matchmaking::MatchmakingRepository;
  MatchmakingRepository repo;
  auto match = repo.find(game_uuid);
  if (!match.has_value()) {
    throw std::runtime_error("match search is already happening");
  }
  repo.remove(game_uuid, creator_key);
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
