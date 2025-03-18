#ifndef ROUTER_H
#define ROUTER_H

#include "route_registry.h"
#include "i_route_registrar.h"
#include <vector>
#include <memory>

class router {
public:
    router();

    void route_request(tcp::socket &socket, http_request &&req);

private:
    void register_all_routes();

    route_registry routes_;
};

#endif // ROUTER_H
