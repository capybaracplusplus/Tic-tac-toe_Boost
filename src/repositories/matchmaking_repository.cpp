#include <nlohmann/json.hpp>
#include <repositories/matchmaking_repository.h>
#include <string>

namespace repositories::matchmaking {
using json = nlohmann::json;

MatchmakingRepository::MatchmakingRepository(
    std::shared_ptr<sw::redis::Redis> dbClient) noexcept
    : dbClient_(std::move(dbClient)) {}

void MatchmakingRepository::add(const std::string &uuid,
                                const std::string &game_password) {
  if (dbClient_->exists(uuid)) {
    throw std::runtime_error("game with this UUID already exists");
  }
  json data;
  data["password"] = game_password;
  dbClient_->set(uuid, data.dump());
}

bool MatchmakingRepository::remove(const std::string &uuid) noexcept {
  return dbClient_->del(uuid) > 0;
}

std::optional<std::string>
MatchmakingRepository::find(const std::string &uuid) noexcept {
  if (!dbClient_->exists(uuid)) {
    return std::nullopt;
  }
  auto val = dbClient_->get(uuid);
  return val;
}
} // namespace repositories::matchmaking
