#include <create_game_handler.h>
#include <http_response.h>
#include <iostream>
#include <boost/log/sources/record_ostream.hpp>
#include <nlohmann/json.hpp>
#include <matchmaking_service.h>

using json = nlohmann::json;

void CreateGameHandler::handle_request(boost::asio::io_context &io_context, tcp::socket &socket,
                                       const http_request &req) {
    HttpResponse response;
    response.set_status(200);
    response.set_header("Content-Type", "text/plain");
    response.set_header("Connection", "keep - alive");
    std::string password = "";
    if (req.body.contains("password")) {
        password = req.body["password"].get<std::string>();
    }
    json res;
    std::string creator_key = MatchmakingService::create(io_context, req.uuid,
                                                         password);
    res["creator_key"] = creator_key;
    response.set_body(res.dump());
    send_response(io_context, socket, response.to_string());
}
