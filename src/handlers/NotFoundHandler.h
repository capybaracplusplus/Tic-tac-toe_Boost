#ifndef NOTFOUNDHANDLER_H
#define NOTFOUNDHANDLER_H

#include <handler.h>
#include <iostream>

class NotFoundHandler : public Handler {
public:
    void handle_request(tcp::socket &socket, const HttpRequest &req) override {
        std::string response = "404 Not Found: The requested path " + req.path + " does not exist.";
        send_response(socket, response);
    }

private:
    void send_response(tcp::socket &socket, const std::string &response) {
        boost::asio::async_write(socket, boost::asio::buffer(response),
                                 [&response](boost::system::error_code ec, std::size_t /*length*/) {
                                     if (!ec) {
                                         std::cout << "Response sent: " << response << std::endl;
                                     }
                                 });
    }
};


#endif //NOTFOUNDHANDLER_H
