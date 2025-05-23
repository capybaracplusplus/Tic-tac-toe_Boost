#include <handlers/handlers.h>
#include <routes/route_registry.h>
#include <routes/routes.h>

void NotifyRoutes::register_routes(route_registry &registry) {
  registry.add_route("/notify", "GET", std::make_shared<NotifyHandler>());
}

void GameRoutes ::register_routes(route_registry &registry) {
  registry.add_route("/game/create", "POST",
                     std::make_shared<CreateGameHandler>());
  registry.add_route("/game/join", "POST", std::make_shared<JoinGameHandler>());
  registry.add_route("/game/remove", "DELETE",
                     std::make_shared<RemoveGameHandler>());
}

void MoveRoutes::register_routes(route_registry &registry) {
  registry.add_route("/move", "POST", std::make_shared<MakeMoveHandler>());
}
