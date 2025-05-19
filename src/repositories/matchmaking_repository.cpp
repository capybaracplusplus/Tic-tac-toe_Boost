#include <nlohmann/json.hpp>
#include <repositories/matchmaking_repository.h>
#include <string>

namespace redis_repos::matchmaking {
sw::redis::Redis redisDbClient = sw::redis::Redis("tcp://127.0.0.1:8081");
using json = nlohmann::json;

MatchmakingRepository::MatchmakingRepository(
    sw::redis::Redis &DbClient) noexcept
    : dbClient_(DbClient) {}

void MatchmakingRepository::add(
    const std::string &uuid, const std::string &game_password) noexcept(false) {
  if (dbClient_.exists(uuid)) {
    throw std::runtime_error("game with this UUID already exists");
  }
  json data;
  data["password"] = game_password;
  redisDbClient.set(uuid, data.dump());
}

bool MatchmakingRepository::remove(const std::string &uuid) noexcept(false) {
  return dbClient_.del(uuid) > 0;
}

std::optional<std::string>
MatchmakingRepository::find(const std::string &uuid) noexcept {
  if (!dbClient_.exists(uuid)) {
    return std::nullopt;
  }
  auto val = dbClient_.get(uuid);
  return val;
}
} // namespace redis_repos::matchmaking
