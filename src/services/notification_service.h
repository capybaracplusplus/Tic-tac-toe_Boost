#ifndef NOTIFICATION_SERVICE_H
#define NOTIFICATION_SERVICE_H

#include <boost/asio/io_context.hpp>
#include <deque>
#include <mutex>
#include <string>
#include <unordered_map>

class NotificationService {
public:
  static void notify(boost::asio::io_context &io_context,
                     const std::string &uuid, const std::string &message);
  static std::string read_notice(boost::asio::io_context &io_context,
                                 const std::string &uuid);

private:
  static std::unordered_map<std::string, std::deque<std::string>> inbox_;
  static std::mutex mutex_;
};

#endif // NOTIFICATION_SERVICE_H
