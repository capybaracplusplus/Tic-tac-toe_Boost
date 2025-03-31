#ifndef HANDLER_H
#define HANDLER_H

#include <boost/asio.hpp>
#include <http_request.h>
#include <string>
using boost::asio::ip::tcp;

class Handler {
public:
  virtual ~Handler() = default;

  virtual void handle_request(boost::asio::io_context &io_context,
                              tcp::socket &socket, const http_request &req) = 0;

protected:
  virtual void send_response(boost::asio::io_context &io_context,
                             tcp::socket &socket, const std::string &response);
};

#endif // HANDLER_H
