#ifndef ROUTES_H
#define ROUTES_H

#include "i_route_registrar.h"
#include "route_registry.h"

class MainRoutes : public i_route_registrar {
public:
    void register_routes(route_registry &registry) override;
};

class IdRoutes : public i_route_registrar {
public:
    void register_routes(route_registry &registry) override;
};

#endif // ROUTES_H
