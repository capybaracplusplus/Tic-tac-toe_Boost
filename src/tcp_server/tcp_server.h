#ifndef SERVER_H
#define SERVER_H

#include <boost/asio.hpp>
#include <memory>
#include <session_manager/session_manager.h>

using boost::asio::ip::tcp;

namespace details {
extern std::shared_ptr<SessionManager> session_manager;
}

class Server {
public:
  explicit Server(boost::asio::io_context &io_context, short port);

private:
  tcp::acceptor acceptor_;
  std::shared_ptr<SessionManager> session_manager_;

  void accept(boost::asio::io_context &io_context);
};

#endif // SERVER_H
