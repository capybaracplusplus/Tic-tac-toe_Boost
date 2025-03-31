#include <boost/asio/read_until.hpp>
#include <boost/log/trivial.hpp>
#include <iostream>
#include <session.h>

router Session::router_;

Session::Session(boost::asio::io_context &io_context, tcp::socket socket)
    : socket_(std::move(socket)), io_context_(io_context) {}

void Session::start() { read_request(); }

void Session::set_uuid(std::string uuid) { uuid_ = uuid; }

void Session::read_request() {
  auto self = shared_from_this();
  boost::asio::async_read_until(
      socket_, buffer_, "\r\n\r\n",
      [this, self](boost::system::error_code ec, std::size_t length) {
        if (!ec) {
          std::istream stream(&buffer_);
          std::string request((std::istreambuf_iterator<char>(stream)),
                              std::istreambuf_iterator<char>());
          http_request parsed_request = process_request(std::move(request));
          parsed_request.uuid = uuid_;
          router_.route_request(io_context_, socket_,
                                std::move(parsed_request));
          read_request();
        } else {
          BOOST_LOG_TRIVIAL(error) << "Exception: " << ec.what();
        }
      });
}
