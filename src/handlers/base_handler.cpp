#include <base_handler.h>
#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>
#include <string>

using boost::asio::ip::tcp;

void Handler::send_response(boost::asio::io_context &io_context,
                            tcp::socket &socket, const std::string &response) {
  boost::asio::async_write(
      socket, boost::asio::buffer(response),
      [](boost::system::error_code ec, std::size_t /*length*/) {
        if (!ec) {
          BOOST_LOG_TRIVIAL(info) << "Response sent";
        } else {
          BOOST_LOG_TRIVIAL(error)
              << "Error sending response: " << ec.message();
        }
      });
}
