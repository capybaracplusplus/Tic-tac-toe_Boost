#include <repositories/matchmaking_repository.h>
#include <string>

namespace redis_repos::matchmaking {
sw::redis::Redis redisDbClient = sw::redis::Redis("tcp://127.0.0.1:8081");

MatchmakingRepository::MatchmakingRepository(
    sw::redis::Redis &DbClient) noexcept
    : dbClient_(DbClient) {}

void MatchmakingRepository::add(
    const std::string &uuid, const std::string &creator_key,
    const std::string &game_password) noexcept(false) {}

bool MatchmakingRepository::remove(
    const std::string &uuid, const std::string &creator_key) noexcept(false) {
  return false;
}

std::optional<std::string>
MatchmakingRepository::find(const std::string &uuid) noexcept {
  return std::nullopt;
}
} // namespace redis_repos::matchmaking
