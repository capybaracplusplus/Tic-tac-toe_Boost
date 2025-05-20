#include <services/notification_service.h>

std::unordered_map<std::string, std::deque<std::string>>
    NotificationService::inbox_;
std::mutex NotificationService::mutex_;

void NotificationService::notify(boost::asio::io_context &io_context,
                                 const std::string &uuid,
                                 const std::string &message) {
  std::lock_guard<std::mutex> lock(mutex_);
  inbox_[uuid].push_back(message);
}

std::string
NotificationService::read_notice(boost::asio::io_context &io_context,
                                 const std::string &uuid) {
  std::lock_guard<std::mutex> lock(mutex_);

  auto it = inbox_.find(uuid);
  if (it == inbox_.end() || it->second.empty()) {
    return "";
  }

  std::string message = std::move(it->second.front());
  it->second.pop_front();

  if (it->second.empty()) {
    inbox_.erase(it);
  }

  return message;
}