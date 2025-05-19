#include <boost/asio.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <handlers/game/remove_game_handler.h>
#include <nlohmann/json.hpp>
#include <services/matchmaking_service.h>
#include <utils/http_response.h>
namespace asio = boost::asio;
using asio::awaitable;
using asio::co_spawn;
using asio::detached;
using asio::use_awaitable;

using json = nlohmann::json;

void RemoveGameHandler::handle_request(boost::asio::io_context &io_context,
                                       tcp::socket &socket,
                                       const http_request &req) {
  HttpResponse response;
  response.set_header("Content-Type", "text/plain");
  response.set_header("Connection", "keep-alive");

  co_spawn(
      io_context, MatchmakingService::remove_game(io_context, req.uuid),
      [response, &io_context, &socket, this](std::exception_ptr e) mutable {
        if (e) {
          try {
            std::rethrow_exception(e);
          } catch (const std::exception &ex) {
            response.set_status(400);
            json res;
            res["error"] = ex.what();
            response.set_body(res.dump());
          }
        } else {
          response.set_status(200);
          response.set_body("{}"); // пустой json для ответа
        }

        // Отправляем ответ здесь, после завершения remove_game
        send_response(io_context, socket, response.to_string());
      });
}