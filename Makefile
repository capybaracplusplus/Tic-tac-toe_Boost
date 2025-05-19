COMPOSE=docker-compose

.PHONY: up down clean restart


up:
	$(COMPOSE) up -d


down:
	$(COMPOSE) down

clean:
	$(COMPOSE) down -v

restart: clean up

run:
	./cmake-build-debug/Tic_Tac_Toe_Boost

start: clean up run_bin