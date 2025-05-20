#include <exceptions/conflict_exception.h>
#include <nlohmann/json.hpp>
#include <repositories/game_repository.h>
#include <repositories/matchmaking_repository.h>
#include <services/matchmaking_service.h>
#include <stdexcept>
#include <string>
#include <utils/redis_client_factory.h>
#include <utils/uuid_generator.h>

std::future<void>
MatchmakingService::create(boost::asio::io_context &io_context,
                           const std::string &creator_uuid,
                           const std::string &game_password) noexcept(false) {
  std::shared_ptr<std::promise<void>> promise_ptr =
      std::make_shared<std::promise<void>>();
  auto future = promise_ptr->get_future();

  io_context.post([creator_uuid, game_password, promise_ptr]() {
    try {
      using repositories::matchmaking::MatchmakingRepository;
      MatchmakingRepository matchmaking_repos;
      auto match = matchmaking_repos.find(creator_uuid);
      if (match.has_value()) {
        throw exceptions::ConflictException(
            "match search is already happening");
      }
      matchmaking_repos.add(creator_uuid, game_password);
      promise_ptr->set_value();
    } catch (...) {
      promise_ptr->set_exception(std::current_exception());
    }
  });
  return future;
}

awaitable<void>
MatchmakingService::remove_game(boost::asio::io_context &io_context,
                                std::string game_uuid) noexcept(false) {
  co_await asio::post(io_context, use_awaitable);
  try {
    using repositories::matchmaking::MatchmakingRepository;
    MatchmakingRepository matchmaking_repos;
    matchmaking_repos.remove(game_uuid);
  } catch (...) {
    throw;
  }
}

std::future<MatchmakingSesion>
MatchmakingService::join(boost::asio::io_context &io_context,
                         const std::string &creator_uuid,
                         const std::string &joining_uuid,
                         const std::string &password) noexcept(false) {
  auto promise_ptr = std::make_shared<std::promise<MatchmakingSesion>>();
  auto future = promise_ptr->get_future();

  io_context.post([creator_uuid, joining_uuid, password, promise_ptr]() {
    try {
      using repositories::game::GameRepository;
      using repositories::matchmaking::MatchmakingRepository;

      MatchmakingRepository matchmaking_repos;
      auto val = matchmaking_repos.find(creator_uuid);
      if (!val.has_value()) {
        throw std::runtime_error("the player you are trying to connect to is "
                                 "not looking for a game");
      }

      nlohmann::json json_object = nlohmann::json::parse(val.value());
      std::string game_password = json_object["password"];
      if (password != game_password) {
        throw std::runtime_error("The password for the game you are trying to "
                                 "connect to is incorrect");
      }

      GameRepository game_repos;
      std::string game_uuid;
      while (true) {
        game_uuid = utils::generate_uuid();
        if (!game_repos.find(game_uuid).has_value()) {
          break;
        }
      }

      MatchmakingSesion new_game_session = {.game_uuid = game_uuid,
                                            .creator_uuid = creator_uuid,
                                            .joining_uuid = joining_uuid};

      game_repos.add(new_game_session);
      promise_ptr->set_value(new_game_session);
    } catch (...) {
      promise_ptr->set_exception(std::current_exception());
    }
  });

  return future;
}
