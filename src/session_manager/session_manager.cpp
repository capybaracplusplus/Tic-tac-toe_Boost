#include <session_manager.h>
#include <uuid_generator.h>

std::string
SessionManager::addSession(const std::shared_ptr<Session> &session) {
  std::string uuidStr = utils::generate_uuid();
  std::lock_guard<std::mutex> lock(mutex_);
  sessions_[uuidStr] = session;
  return uuidStr;
}

std::shared_ptr<Session> SessionManager::getSession(const std::string &uuid) {
  std::lock_guard<std::mutex> lock(mutex_);
  auto it = sessions_.find(uuid);
  return (it != sessions_.end()) ? it->second : nullptr;
}

void SessionManager::removeSession(const std::string &uuid) {
  std::lock_guard<std::mutex> lock(mutex_);
  sessions_.erase(uuid);
}
