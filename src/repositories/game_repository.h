#ifndef GAME_REPOSITORY_H
#define GAME_REPOSITORY_H

namespace redis_repos::game {
#include <sw/redis++/redis++.h>

extern sw::redis::Redis redisDbClient;

class GameRepository {
public:
  GameRepository(sw::redis::Redis &DbClient = redisDbClient) noexcept;

  std::optional<std::string> find(const std::string &uuid) noexcept;

private:
  sw::redis::Redis &dbClient_;
};
} // namespace redis_repos::game

#endif // GAME_REPOSITORY_H
