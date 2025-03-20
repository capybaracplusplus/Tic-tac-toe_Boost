#ifndef REMOVE_GAME_HANDLER_H
#define REMOVE_GAME_HANDLER_H

class RemoveGameHandler : public Handler {
public:
    void handle_request(tcp::socket &socket, const http_request &req) override {
        HttpResponse response;
        response.set_status(200);
        response.set_header("Content-Type", "text/plain");
        response.set_header("Connection", "close");
        response.set_body("aboba");
        send_response(socket, response.to_string());
    }
};

#endif //REMOVE_GAME_HANDLER_H
