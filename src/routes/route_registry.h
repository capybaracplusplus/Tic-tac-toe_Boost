#ifndef ROUTE_REGISTRY_H
#define ROUTE_REGISTRY_H

#include <handlers.h>
#include <http_request.h>
#include <unordered_map>
#include <memory>
#include <mutex>

class route_registry {
public:
    using RouteTable = std::unordered_map<std::string, std::unordered_map<std::string, std::shared_ptr<Handler> > >;

    void add_route(const std::string &path, const std::string &method, std::shared_ptr<Handler> handler);

    std::shared_ptr<Handler> get_handler(const std::string &path, const std::string &method);

private:
    RouteTable routes_;
    std::mutex mutex_;
};

#endif // ROUTE_REGISTRY_H
