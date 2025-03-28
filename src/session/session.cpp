#include <session.h>
#include <iostream>

router Session::router_;

Session::Session(boost::asio::io_context &io_context, tcp::socket socket)
    : socket_(std::move(socket)), io_context_(io_context) {
}

void Session::start() {
    read_request();
}

void Session::set_uuid(std::string uuid) {
    uuid_ = uuid;
}

void Session::read_request() {
    auto self = shared_from_this();
    socket_.async_read_some(boost::asio::buffer(data_, 8192),
                            [this, self](boost::system::error_code ec, std::size_t length) {
                                if (!ec) {
                                    std::string request(data_, length);
                                    http_request parsed_request = process_request(std::move(request));
                                    parsed_request.uuid = uuid_;
                                    router_.route_request(io_context_, socket_, std::move(parsed_request));
                                }
                            });
}
