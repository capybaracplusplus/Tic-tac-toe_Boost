#ifndef SESSION_MANAGER_H
#define SESSION_MANAGER_H

#include <memory>
#include <unordered_map>

class Session;

class SessionManager {
public:
  std::string addSession(const std::shared_ptr<Session> &session);

  std::shared_ptr<Session> getSession(const std::string &uuid);

  void removeSession(const std::string &uuid);

private:
  std::unordered_map<std::string, std::shared_ptr<Session>> sessions_;
  std::mutex mutex_;
};

#endif // SESSION_MANAGER_H
