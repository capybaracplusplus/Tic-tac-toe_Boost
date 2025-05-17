#ifndef ROUTES_H
#define ROUTES_H

#include <routes/i_route_registrar.h>

class MainRoutes : public i_route_registrar {
public:
  void register_routes(route_registry &registry) override;
};

class GameRoutes : public i_route_registrar {
public:
  void register_routes(route_registry &registry) override;
};

class MoveRoutes : public i_route_registrar {
public:
  void register_routes(route_registry &registry) override;
};

#endif // ROUTES_H
