#ifndef MAIN_HANDLER_H
#define MAIN_HANDLER_H

#include <base_handler.h>

class MainHandler : public Handler {
public:
    void handle_request(tcp::socket &socket, const http_request &req) override {
        std::string response =
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/plain\r\n"
                "Content-Length: 5\r\n"
                "Connection: close\r\n"
                "\r\n"
                "aboba";
        send_response(socket, response);
    }

private:
    void send_response(tcp::socket &socket, const std::string &response) {
        boost::asio::async_write(socket, boost::asio::buffer(response),
                                 [](boost::system::error_code ec, std::size_t /*length*/) {
                                     if (!ec) {
                                         std::cout << "Response sent" << std::endl;
                                     } else {
                                         std::cerr << "Error sending response: " << ec.message() << std::endl;
                                     }
                                 });
    }
};


#endif //MAIN_HANDLER_H
