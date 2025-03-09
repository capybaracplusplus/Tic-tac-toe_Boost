#ifndef MAIN_HANDLER_H
#define MAIN_HANDLER_H

#include <handler.h>

class MainHandler : public Handler {
public:
    void handle_request(tcp::socket &socket, const HttpRequest &req) override {
        std::string response = "aboba";
        send_response(socket, response);
    }

private:
    void send_response(tcp::socket &socket, const std::string &response) {
        boost::asio::async_write(socket, boost::asio::buffer(response),
                                 [](boost::system::error_code ec, std::size_t /*length*/) {
                                     if (!ec) {
                                         std::cout << "Response sent" << std::endl;
                                     }
                                 });
    }
};



#endif //MAIN_HANDLER_H
