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
  response.set_status(201);
  response.set_header("Content-Type", "text/plain");
  response.set_header("Connection", "keep - alive");
  std::string password = "";
  if (req.body.contains("password")) {
    password = req.body["password"].get<std::string>();
  }
  json res;
  std::string creator_key =
      MatchmakingService::create(io_context, req.uuid, password);
  res["creator_key"] = creator_key;
  res["game_id"] = req.uuid;
  response.set_body(res.dump());
  send_response(io_context, socket, response.to_string());
}
