#ifndef REDIS_REPOS_H
#define REDIS_REPOS_H

#include <sw/redis++/redis++.h>

namespace repos {
extern sw::redis::Redis redisDbClient;

class Session {
public:
  bool create_session();

private:
  sw::redis::Redis &dbClient_ = redisDbClient;
};
} // namespace repos

#endif // REDIS_REPOS_H
