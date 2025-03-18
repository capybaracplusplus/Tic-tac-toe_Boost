#include "routes.h"
#include <handlers.h>

void MainRoutes::register_routes(route_registry &registry) {
    registry.add_route("/", "GET", std::make_shared<MainHandler>());
}

void IdRoutes::register_routes(route_registry &registry) {
    registry.add_route("/id", "GET", std::make_shared<IdHandler>());
}
