#ifndef HANDLER_H
#define HANDLER_H

#include<iostream>
#include <string>
#include <http_request.h>
#include <boost/asio.hpp>
using boost::asio::ip::tcp;

class Handler {
public:
    virtual ~Handler() = default;

    virtual void handle_request(tcp::socket &socket, const http_request &req) = 0;

protected:
    virtual void send_response(tcp::socket &socket, const std::string &response) {
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

#endif //HANDLER_H
