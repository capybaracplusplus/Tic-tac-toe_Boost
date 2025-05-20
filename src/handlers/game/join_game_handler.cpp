#include <boost/log/trivial.hpp>
#include <handlers/game/join_game_handler.h>
#include <nlohmann/json.hpp>
#include <services/matchmaking_service.h>
#include <services/notification_service.h>
#include <utils/http_response.h>

using json = nlohmann::json;

void JoinGameHandler::handle_request(boost::asio::io_context &io_context,
                                     tcp::socket &socket,
                                     const http_request &req) {
  HttpResponse response;
  response.set_header("Content-Type", "application/json");
  response.set_header("Connection", "keep-alive");

  std::string game_id = "";
  std::string password = "";
  if (req.body.contains("game_id")) {
    game_id = req.body["game_id"].get<std::string>();
  }
  if (req.body.contains("password")) {
    password = req.body["password"].get<std::string>();
  }
  json res;
  try {
    auto future =
        MatchmakingService::join(io_context, game_id, req.uuid, password);
    MatchmakingSesion game_sesion = future.get();
    response.set_status(201);
    res["game_id"] = game_sesion.game_uuid;
    auto body = res.dump();
    response.set_body(body);
    response.set_header("Content-Length", std::to_string(res.dump().size()));

    send_response(io_context, socket, response.to_string());

    try {
      auto future_notify =
          NotificationService::notify(io_context, game_id, body);
      future_notify.get();
    } catch (const std::exception &notify_error) {
      BOOST_LOG_TRIVIAL(error)
          << "Notification failed: " << notify_error.what();
    }
  } catch (const std::exception &e) {
    response.set_status(400);
    res["error"] = e.what();
    response.set_body(res.dump());
    response.set_header("Content-Length", std::to_string(res.dump().size()));
    send_response(io_context, socket, response.to_string());
  }
}
