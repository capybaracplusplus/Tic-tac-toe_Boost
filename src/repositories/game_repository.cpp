#include "game_repository.h"

namespace redis_repos::game {
sw::redis::Redis redisDbClient = sw::redis::Redis("tcp://127.0.0.1:8082");

GameRepository::GameRepository(sw::redis::Redis &DbClient) noexcept
    : dbClient_(DbClient) {}

std::optional<std::string>
GameRepository::find(const std::string &uuid) noexcept {
  return std::optional<std::string>();
}
} // namespace redis_repos::game
