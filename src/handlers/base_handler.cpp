#include <base_handler.h>
#include <http_request.h>
#include <boost/asio.hpp>
#include<iostream>
#include <string>


using boost::asio::ip::tcp;


void Handler::send_response(tcp::socket &socket, const std::string &response) {
    boost::asio::async_write(socket, boost::asio::buffer(response),
                             [](boost::system::error_code ec, std::size_t /*length*/) {
                                 if (!ec) {
                                     std::cout << "Response sent" << std::endl;
                                 } else {
                                     std::cerr << "Error sending response: " << ec.message() << std::endl;
                                 }
                             });
}
