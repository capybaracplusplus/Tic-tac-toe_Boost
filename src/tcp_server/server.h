#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <unordered_map>
#include <boost/asio.hpp>
#include <handlers.h>
#include <HttpRequest.h>
#include <router.h>

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
public:
    explicit Session(tcp::socket socket);

    void start();

private:
    void read_request();

private:
    tcp::socket socket_;
    char data_[1024];
    static Router router_;
};

class Server {
public:
    Server(boost::asio::io_context &io_context, short port);

private:
    tcp::acceptor acceptor_;

    void accept();
};

#endif // SERVER_H
