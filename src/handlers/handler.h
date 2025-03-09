#ifndef HANDLER_H
#define HANDLER_H

#include <string>
#include <HttpRequest.h>
#include <boost/asio.hpp>
using boost::asio::ip::tcp;

class Handler {
public:
    virtual void handle_request(tcp::socket &socket, const HttpRequest &req) = 0;
};

#endif //HANDLER_H
