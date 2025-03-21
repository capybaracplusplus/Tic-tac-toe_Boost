#ifndef CREATE_GAME_HANDLER_H
#define CREATE_GAME_HANDLER_H

#include <base_handler.h>

class CreateGameHandler : public Handler {
public:
    void handle_request(boost::asio::io_context &io_context, tcp::socket &socket, const http_request &req) override;
};

#endif //CREATE_GAME_HANDLER_H
