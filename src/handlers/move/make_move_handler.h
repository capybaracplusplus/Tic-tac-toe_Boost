#ifndef MAKE_MOVE_HANDLER_H
#define MAKE_MOVE_HANDLER_H

#include <base_handler.h>

class MakeMoveHandler : public Handler {
public:
    void handle_request(tcp::socket &socket, const http_request &req) override;
};

#endif //MAKE_MOVE_HANDLER_H
