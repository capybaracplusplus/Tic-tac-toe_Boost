#include <tcp_server.h>

router Session::router_;

Session::Session(boost::asio::io_context &io_context, tcp::socket socket)
    : socket_(std::move(socket)), io_context_(io_context) {
}

void Session::start() {
    read_request();
}

void Session::read_request() {
    auto self = shared_from_this();
    socket_.async_read_some(boost::asio::buffer(data_, 1024),
                            [this, self](boost::system::error_code ec, std::size_t length) {
                                if (!ec) {
                                    std::string request(data_, length);
                                    http_request parsed_request = process_request(std::move(request));
                                    router_.route_request(io_context_, socket_, std::move(parsed_request));
                                }
                            });
}

Server::Server(boost::asio::io_context &io_context, short port)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
    accept(io_context);
}

void Server::accept(boost::asio::io_context &io_context) {
    acceptor_.async_accept(
        [this,&io_context](boost::system::error_code ec, tcp::socket socket) {
            if (!ec) {
                std::make_shared<Session>(io_context, std::move(socket))->start();
            }
            accept(io_context);
        });
}
