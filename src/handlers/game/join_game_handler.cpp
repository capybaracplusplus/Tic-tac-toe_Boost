#include <join_game_handler.h>
#include <http_response.h>

void JoinGameHandler::handle_request(tcp::socket &socket, const http_request &req) {
    HttpResponse response;
    response.set_status(200);
    response.set_header("Content-Type", "text/plain");
    response.set_header("Connection", "close");
    response.set_body("JoinGameHandler");
    send_response(socket, response.to_string());
}
