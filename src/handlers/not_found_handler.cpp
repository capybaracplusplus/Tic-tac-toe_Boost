#include <not_found_handler.h>

void NotFoundHandler::handle_request(boost::asio::io_context &io_context, tcp::socket &socket,
                                     const http_request &req) {
    std::string response_body = "404 Not Found: The requested path " + req.path + " does not exist.";
    std::string response =
            "HTTP/1.1 404 Not Found\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: " + std::to_string(response_body.size()) + "\r\n"
            "Connection: close\r\n"
            "\r\n" +
            response_body;
    send_response(io_context, socket, response);
}
