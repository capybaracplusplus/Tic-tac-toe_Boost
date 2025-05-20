#include <boost/log/sources/record_ostream.hpp>
#include <handlers/game/create_game_handler.h>
#include <nlohmann/json.hpp>
#include <services/matchmaking_service.h>
#include <utils/http_request.h>
#include <utils/http_response.h>

using json = nlohmann::json;

void CreateGameHandler::handle_request(boost::asio::io_context &io_context,
                                       tcp::socket &socket,
                                       const http_request &req) {
  HttpResponse response;
  response.set_header("Content-Type", "application/json");
  response.set_header("Connection", "keep-alive");
  std::string password = "";
  if (req.body.contains("password")) {
    password = req.body["password"].get<std::string>();
  }
  json res;
  try {
    auto future = MatchmakingService::create(io_context, req.uuid, password);
    future.get();
    res["game_id"] = req.uuid;
    response.set_status(201);
    response.set_body(res.dump());
    response.set_header("Content-Length", std::to_string(res.dump().size()));
  } catch (const std::exception &e) {
    response.set_status(409);
    res["error"] = e.what();
    response.set_body(res.dump());
    response.set_header("Content-Length", std::to_string(res.dump().size()));
  }
  send_response(io_context, socket, response.to_string());
}
