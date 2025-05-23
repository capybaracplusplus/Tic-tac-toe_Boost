#include <boost/log/trivial.hpp>
#include <tcp_server/tcp_server.h>

int main() try {
  boost::asio::io_context io_context;
  Server server(io_context, 8080);

  size_t num_threads = std::thread::hardware_concurrency();
  std::vector<std::thread> threads;

  for (size_t i = 0; i < num_threads; ++i) {
    threads.emplace_back([&io_context]() { io_context.run(); });
  }

  for (auto &thread : threads) {
    thread.join();
  }
} catch (std::exception &e) {
  BOOST_LOG_TRIVIAL(error) << "Exception: " << e.what();
}
