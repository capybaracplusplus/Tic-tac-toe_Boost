#ifndef JOIN_GAME_HANDLER_H
#define JOIN_GAME_HANDLER_H

#include <base_handler.h>

class JoinGameHandler : public Handler {
public:
    void handle_request(boost::asio::io_context &io_context, tcp::socket &socket, const http_request &req) override;
};

#endif //JOIN_GAME_HANDLER_H
