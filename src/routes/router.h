#ifndef ROUTER_H
#define ROUTER_H

#include <handlers.h>
#include <HttpRequest.h>
#include <mutex>

class Router {
public:
    Router() {
        routes_["/"] = std::make_shared<MainHandler>();
        routes_["/id"] = std::make_shared<IdHandler>();
    }

    void route_request(tcp::socket &socket, HttpRequest &&req) {
        std::lock_guard<std::mutex> lock(mutex_);

        auto it = routes_.find(req.path);
        if (it != routes_.end()) {
            it->second->handle_request(socket, std::move(req));
        } else {
            NotFoundHandler not_found_handler;
            not_found_handler.handle_request(socket, std::move(req));
        }
    }

private:
    std::unordered_map<std::string, std::shared_ptr<Handler> > routes_;
    std::mutex mutex_;
};


#endif //ROUTER_H
