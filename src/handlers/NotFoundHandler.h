#ifndef NOTFOUNDHANDLER_H
#define NOTFOUNDHANDLER_H

#include <handler.h>
#include <iostream>

class NotFoundHandler : public Handler {
public:
    void handle_request(tcp::socket &socket, const HttpRequest &req) override {
        std::string response_body = "404 Not Found: The requested path " + req.path + " does not exist.";
        std::string response =
                "HTTP/1.1 404 Not Found\r\n"
                "Content-Type: text/plain\r\n"
                "Content-Length: " + std::to_string(response_body.size()) + "\r\n"
                "Connection: close\r\n"
                "\r\n" +
                response_body;
        send_response(socket, response);
    }

private:
    void send_response(tcp::socket &socket, const std::string &response) {
        auto buffer = std::make_shared<std::string>(std::move(response));
        boost::asio::async_write(socket, boost::asio::buffer(*buffer),
                                 [buffer](boost::system::error_code ec, std::size_t /*length*/) {
                                     if (!ec) {
                                         std::cout << "Response sent: " << *buffer << std::endl;
                                     } else {
                                         std::cerr << "Error sending response: " << ec.message() << std::endl;
                                     }
                                 });
    }
};


#endif //NOTFOUNDHANDLER_H
