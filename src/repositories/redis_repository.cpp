#include <redis_repository.h>

namespace repos {
sw::redis::Redis redisDbClient = sw::redis::Redis("tcp://127.0.0.1:6379");
}
