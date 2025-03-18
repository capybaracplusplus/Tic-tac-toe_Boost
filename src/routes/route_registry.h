#ifndef ROUTE_REGISTRY_H
#define ROUTE_REGISTRY_H

#include <handlers.h>
#include <http_request.h>
#include <unordered_map>
#include <memory>
#include <mutex>

class route_registry {
public:
    using RouteTable = std::unordered_map<std::string, std::unordered_map<std::string, std::shared_ptr<Handler>>>;

    void add_route(const std::string &path, const std::string &method, std::shared_ptr<Handler> handler) {
        std::lock_guard<std::mutex> lock(mutex_);
        routes_[path][method] = std::move(handler);
    }

    std::shared_ptr<Handler> get_handler(const std::string &path, const std::string &method) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto path_it = routes_.find(path);
        if (path_it != routes_.end()) {
            auto method_it = path_it->second.find(method);
            if (method_it != path_it->second.end()) {
                return method_it->second;
            }
        }
        return nullptr;
    }

private:
    RouteTable routes_;
    std::mutex mutex_;
};

#endif // ROUTE_REGISTRY_H
