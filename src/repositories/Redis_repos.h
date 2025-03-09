#ifndef REDIS_REPOS_H
#define REDIS_REPOS_H

#include <sw/redis++/redis++.h>


namespace repos {
    extern sw::redis::Redis redisDbClient;

    class Session {
    public:
        // ...
    private:
        sw::redis::Redis &dbClient_ = redisDbClient;
    };
}

#endif //REDIS_REPOS_H
