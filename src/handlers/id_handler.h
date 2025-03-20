#ifndef GET_ID_HANDLER_H
#define GET_ID_HANDLER_H
#include <iostream>
#include <base_handler.h>

class IdHandler : public Handler {
public:
    void handle_request(tcp::socket &socket, const http_request &req) override {
        std::string response = "ID:";
        send_response(socket, response);
    }
};


#endif //GET_ID_HANDLER_H
