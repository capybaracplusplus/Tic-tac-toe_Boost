#ifndef GET_ID_HANDLER_H
#define GET_ID_HANDLER_H
#include <iostream>
#include <base_handler.h>

class IdHandler : public Handler {
public:
    void handle_request(tcp::socket &socket, const http_request &req) override {
        std::string response = "ID:";
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


#endif //GET_ID_HANDLER_H
