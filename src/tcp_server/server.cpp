#include <server.h>

Router Session::router_;

Session::Session(tcp::socket socket)
    : socket_(std::move(socket)) {
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
                                    std::cout << "Received: " << request << std::endl;

                                    HttpRequest parsed_request = process_request(std::move(request));
                                    router_.route_request(socket_, std::move(parsed_request));
                                }
                            });
}


Server::Server(boost::asio::io_context &io_context, short port)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
    accept();
}


void Server::accept() {
    acceptor_.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket) {
            if (!ec) {
                std::make_shared<Session>(std::move(socket))->start();
            }
            accept();
        });
}
