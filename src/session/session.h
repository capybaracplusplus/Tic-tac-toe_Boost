#ifndef SESSION_H
#define SESSION_H

#include <boost/asio.hpp>
#include <router.h>

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
public:
    explicit Session(boost::asio::io_context &io_context, tcp::socket socket);

    void start();

    void set_uuid(std::string uuid);

private:
    void read_request();

private:
    tcp::socket socket_;
    boost::asio::io_context &io_context_;
    boost::asio::streambuf buffer_;
    static router router_;
    std::string uuid_;
};

#endif //SESSION_H
