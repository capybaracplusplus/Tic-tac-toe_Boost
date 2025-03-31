#ifndef IROUTE_REGISTRAR_H
#define IROUTE_REGISTRAR_H

class route_registry;

class i_route_registrar {
public:
  virtual void register_routes(route_registry &registry) = 0;
  virtual ~i_route_registrar() = default;
};

#endif // IROUTE_REGISTRAR_H
