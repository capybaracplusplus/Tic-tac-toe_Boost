#ifndef REDIS_REPOS_MATCHMAKING_H
#define REDIS_REPOS_MATCHMAKING_H

#include <sw/redis++/redis++.h>
namespace redis_repos::matchmaking {

extern sw::redis::Redis redisDbClient;

class MatchmakingRepository {
public:
  MatchmakingRepository(sw::redis::Redis &DbClient = redisDbClient) noexcept;

  void add(const std::string &uuid,
           const std::string &game_password) noexcept(false);

  bool remove(const std::string &uuid) noexcept(false);

  std::optional<std::string> find(const std::string &uuid) noexcept;

private:
  sw::redis::Redis &dbClient_;
};
} // namespace redis_repos::matchmaking

#endif // REDIS_REPOS_MATCHMAKING_H
