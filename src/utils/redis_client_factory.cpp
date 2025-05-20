#include <utils/redis_client_factory.h>

std::shared_ptr<sw::redis::Redis> create_redis_client(const std::string &url) {
  return std::make_shared<sw::redis::Redis>(url);
}

std::shared_ptr<sw::redis::Redis> create_matchmaking_redis_client() {
  return std::make_shared<sw::redis::Redis>("tcp://127.0.0.1:8081");
}

std::shared_ptr<sw::redis::Redis> create_game_redis_client() {
  return std::make_shared<sw::redis::Redis>("tcp://127.0.0.1:8082");
}