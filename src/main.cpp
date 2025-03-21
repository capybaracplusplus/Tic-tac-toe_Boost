#include <tcp_server.h>

int main() try {
    boost::asio::io_context io_context;
    Server server(io_context, 8080);
    io_context.run();
} catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << std::endl;
}
