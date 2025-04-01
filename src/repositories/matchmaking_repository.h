#ifndef REDIS_REPOS_MATCHMAKING_H
#define REDIS_REPOS_MATCHMAKING_H

namespace redis_repos::matchmaking {
#include <sw/redis++/redis++.h>

extern sw::redis::Redis redisDbClient;

class MatchmakingRepository {
public:
  MatchmakingRepository(sw::redis::Redis &DbClient = redisDbClient) noexcept;

  void add(const std::string &uuid, const std::string &creator_key,
           const std::string &game_password) noexcept(false);

  bool remove(const std::string &uuid,
              const std::string &creator_key) noexcept(false);

  std::optional<std::string> find(const std::string &uuid) noexcept;

private:
  sw::redis::Redis &dbClient_;
};
} // namespace redis_repos::matchmaking

#endif // REDIS_REPOS_MATCHMAKING_H
