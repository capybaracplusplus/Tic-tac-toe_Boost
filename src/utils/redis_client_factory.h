#ifndef TIC_TAC_TOE_BOOST_REDIS_CLIENT_FACTORY_H
#define TIC_TAC_TOE_BOOST_REDIS_CLIENT_FACTORY_H

#include <memory>
#include <sw/redis++/redis++.h>

std::shared_ptr<sw::redis::Redis> create_redis_client(const std::string &url);

std::shared_ptr<sw::redis::Redis> create_matchmaking_redis_client();

std::shared_ptr<sw::redis::Redis> create_game_redis_client();

#endif // TIC_TAC_TOE_BOOST_REDIS_CLIENT_FACTORY_H
