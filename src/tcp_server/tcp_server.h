#ifndef SERVER_H
#define SERVER_H

#include <boost/asio.hpp>
#include <router.h>

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
public:
    explicit Session(boost::asio::io_context &io_context, tcp::socket socket);

    void start();

private:
    void read_request();

private:
    tcp::socket socket_;
    boost::asio::io_context &io_context_;
    char data_[1024];
    static router router_;
};

class Server {
public:
    Server(boost::asio::io_context &io_context, short port);

private:
    tcp::acceptor acceptor_;

    void accept(boost::asio::io_context& io_context);
};

#endif // SERVER_H
