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
    virtual void send_response(tcp::socket &socket, const std::string &response);
};

#endif //HANDLER_H
