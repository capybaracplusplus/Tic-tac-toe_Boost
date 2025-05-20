#ifndef REDIS_REPOS_MATCHMAKING_H
#define REDIS_REPOS_MATCHMAKING_H

#include <utils/redis_client_factory.h>

namespace repositories::matchmaking {

class MatchmakingRepository {
public:
  MatchmakingRepository(std::shared_ptr<sw::redis::Redis> dbClient =
                            create_matchmaking_redis_client()) noexcept;

  void add(const std::string &uuid, const std::string &game_password);

  bool remove(const std::string &uuid) noexcept;

  std::optional<std::string> find(const std::string &uuid) noexcept;

private:
  std::shared_ptr<sw::redis::Redis> dbClient_;
};
} // namespace repositories::matchmaking

#endif // REDIS_REPOS_MATCHMAKING_H
