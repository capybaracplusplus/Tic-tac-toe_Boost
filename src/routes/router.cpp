#include <handlers/handlers.h>
#include <routes/router.h>
#include <routes/routes.h>

router::router() { register_all_routes(); }

void router::route_request(boost::asio::io_context &io_context,
                           tcp::socket &socket, http_request &&req) {
  auto handler = routes_.get_handler(req.path, req.method);
  if (handler) {
    handler->handle_request(io_context, socket, std::move(req));
  } else {
    NotFoundHandler().handle_request(io_context, socket, std::move(req));
  }
}

void router::register_all_routes() {
  std::vector<std::shared_ptr<i_route_registrar>> route_modules = {
      std::make_shared<MainRoutes>(),
      std::make_shared<GameRoutes>(),
      std::make_shared<MoveRoutes>(),
  };

  for (const auto &module : route_modules) {
    module->register_routes(routes_);
  }
}
