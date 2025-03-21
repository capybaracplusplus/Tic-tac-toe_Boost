#ifndef MAIN_HANDLER_H
#define MAIN_HANDLER_H

#include <base_handler.h>

class MainHandler : public Handler {
public:
    void handle_request(boost::asio::io_context &io_context, tcp::socket &socket, const http_request &req) override;
};


#endif //MAIN_HANDLER_H
