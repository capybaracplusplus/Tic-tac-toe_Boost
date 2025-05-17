#include <handlers/game/remove_game_handler.h>
#include <utils/http_response.h>

void RemoveGameHandler::handle_request(boost::asio::io_context &io_context,
                                       tcp::socket &socket,
                                       const http_request &req) {
  HttpResponse response;
  response.set_status(200);
  response.set_header("Content-Type", "text/plain");
  response.set_header("Connection", "close");
  response.set_body("RemoveGameHandler");
  send_response(io_context, socket, response.to_string());
}
