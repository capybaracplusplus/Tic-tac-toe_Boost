#ifndef GAME_REPOSITORY_H
#define GAME_REPOSITORY_H

#include <utils/matchmaking_sesion.h>
#include <utils/redis_client_factory.h>

namespace repositories::game {

class GameRepository {
public:
  GameRepository(std::shared_ptr<sw::redis::Redis> dbClient =
                     create_game_redis_client()) noexcept;

  void add(const MatchmakingSesion &) noexcept;

  bool remove(void);

  std::optional<std::string> find(const std::string &uuid) noexcept;

private:
  std::shared_ptr<sw::redis::Redis> dbClient_;
};
} // namespace repositories::game

#endif // GAME_REPOSITORY_H
