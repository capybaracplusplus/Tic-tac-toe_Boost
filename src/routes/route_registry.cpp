#include <route_registry.h>

void route_registry::add_route(const std::string &path,
                               const std::string &method,
                               std::shared_ptr<Handler> handler) {
  routes_[path][method] = std::move(handler);
}

std::shared_ptr<Handler>
route_registry::get_handler(const std::string &path,
                            const std::string &method) {
  auto path_it = routes_.find(path);
  if (path_it != routes_.end()) {
    auto method_it = path_it->second.find(method);
    if (method_it != path_it->second.end()) {
      return method_it->second;
    }
  }
  return nullptr;
}
