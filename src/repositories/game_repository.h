#ifndef GAME_REPOSITORY_H
#define GAME_REPOSITORY_H

#include <sw/redis++/redis++.h>
#include <utils/matchmaking_sesion.h>

namespace redis_repos::game {

extern sw::redis::Redis redisDbClient;

class GameRepository {
public:
  GameRepository(sw::redis::Redis &DbClient = redisDbClient) noexcept;

  void add(const MatchmakingSesion &) noexcept;

  bool remove(void) noexcept(false);

  std::optional<std::string> find(const std::string &uuid) noexcept;

private:
  sw::redis::Redis &dbClient_;
};
} // namespace redis_repos::game

#endif // GAME_REPOSITORY_H
