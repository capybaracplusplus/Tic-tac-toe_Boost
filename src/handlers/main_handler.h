#ifndef MAIN_HANDLER_H
#define MAIN_HANDLER_H

#include <base_handler.h>

class MainHandler : public Handler {
public:
    void handle_request(tcp::socket &socket, const http_request &req) override {
        std::string response =
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/plain\r\n"
                "Content-Length: 5\r\n"
                "Connection: close\r\n"
                "\r\n"
                "aboba";
        send_response(socket, response);
    }
};


#endif //MAIN_HANDLER_H
