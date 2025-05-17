#include <session/session.h>
#include <tcp_server/tcp_server.h>

namespace details {
auto session_manager = std::make_shared<SessionManager>();
}

Server::Server(boost::asio::io_context &io_context, short port)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)),
      session_manager_(details::session_manager) {
  accept(io_context);
}

void Server::accept(boost::asio::io_context &io_context) {
  acceptor_.async_accept(
      [this, &io_context](boost::system::error_code ec, tcp::socket socket) {
        if (!ec) {
          auto new_session =
              std::make_shared<Session>(io_context, std::move(socket));
          new_session->set_uuid(session_manager_->addSession(new_session));
          new_session->start();
        }
        accept(io_context);
      });
}
