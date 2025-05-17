#ifndef MAKE_MOVE_HANDLER_H
#define MAKE_MOVE_HANDLER_H

#include <handlers/base_handler.h>

class MakeMoveHandler : public Handler {
public:
  void handle_request(boost::asio::io_context &io_context, tcp::socket &socket,
                      const http_request &req) override;
};

#endif // MAKE_MOVE_HANDLER_H
