#ifndef MATCHMAKING_SERVICE_H
#define MATCHMAKING_SERVICE_H

#include <boost/asio.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <future>
#include <string>
#include <utils/matchmaking_sesion.h>
namespace asio = boost::asio;
using asio::awaitable;
using asio::co_spawn;
using asio::detached;
using asio::use_awaitable;

class MatchmakingService {
public:
  static std::future<void>
  create(boost::asio::io_context &io_context, const std::string &creator_uuid,
         const std::string &game_password) noexcept(false);

  static awaitable<void> remove_game(boost::asio::io_context &io_context,
                                     std::string game_uuid) noexcept(false);

  static std::future<MatchmakingSesion>
  join(boost::asio::io_context &io_context, const std::string &creator_uuid,
       const std::string &joining_uuid,
       const std::string &password) noexcept(false);
};

#endif // MATCHMAKING_SERVICE_H
