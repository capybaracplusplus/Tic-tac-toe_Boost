#ifndef ROUTER_H
#define ROUTER_H

#include "route_registry.h"

class router {
public:
  router();

  void route_request(boost::asio::io_context &io_context, tcp::socket &socket,
                     http_request &&req);

private:
  void register_all_routes();

  route_registry routes_;
};

#endif // ROUTER_H
