#ifndef NOTFOUNDHANDLER_H
#define NOTFOUNDHANDLER_H

#include <base_handler.h>

class NotFoundHandler : public Handler {
public:
    void handle_request(tcp::socket &socket, const http_request &req) override;
};


#endif //NOTFOUNDHANDLER_H
