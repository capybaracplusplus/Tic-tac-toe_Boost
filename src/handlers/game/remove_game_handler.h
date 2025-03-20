#ifndef REMOVE_GAME_HANDLER_H
#define REMOVE_GAME_HANDLER_H

#include <base_handler.h>

class RemoveGameHandler : public Handler {
public:
    void handle_request(tcp::socket &socket, const http_request &req) override;
};

#endif //REMOVE_GAME_HANDLER_H
