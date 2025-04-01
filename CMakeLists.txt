cmake_minimum_required(VERSION 3.28)
cmake_policy(SET CMP0167 OLD)
project(Tic_Tac_Toe_Boost)

set(CMAKE_CXX_STANDARD 23)

# <----------------------------- Add Executable ----------------------------->
add_executable(Tic_Tac_Toe_Boost
        src/main.cpp
        src/utils/uuid_generator.h
        src/utils/jwt_token.h src/utils/jwt_token.cpp
        src/utils/http_request.h src/utils/http_request.cpp
        src/utils/http_response.h src/utils/http_response.cpp
        src/tcp_server/tcp_server.h src/tcp_server/tcp_server.cpp
        src/session_manager/session_manager.h src/session_manager/session_manager.cpp
        src/session/session.cpp src/session/session.h
        src/routes/Router.h src/routes/Router.cpp
        src/routes/i_route_registrar.h
        src/routes/route_registry.h src/routes/route_registry.cpp
        src/routes/Routes.h src/routes/Routes.cpp
        src/handlers/game/create_game_handler.h src/handlers/game/create_game_handler.cpp
        src/handlers/game/join_game_handler.h src/handlers/game/join_game_handler.cpp
        src/handlers/game/remove_game_handler.h src/handlers/game/remove_game_handler.cpp
        src/handlers/game/game_handlers.h
        src/handlers/move/make_move_handler.h src/handlers/move/make_move_handler.cpp
        src/handlers/move/move_handlers.h
        src/handlers/main_handler.h src/handlers/main_handler.cpp
        src/handlers/not_found_handler.h src/handlers/not_found_handler.cpp
        src/handlers/base_handler.h src/handlers/base_handler.cpp
        src/handlers/handlers.h
        src/services/game_service.h src/services/game_service.cpp
        src/services/move_service.h src/services/move_service.cpp
        src/services/matchmaking_service.h src/services/matchmaking_service.cpp
        src/services/notification_service.h src/services/notification_service.cpp
        src/repositories/matchmaking_repository.h src/repositories/matchmaking_repository.cpp
)

# <---------------------------- Include Directories ---------------------------->
file(GLOB_RECURSE HANDLER_HEADERS ${CMAKE_SOURCE_DIR}/src/handlers/*.h)

set(HANDLER_DIRS "")
foreach(header ${HANDLER_HEADERS})
    get_filename_component(dir ${header} DIRECTORY)
    list(APPEND HANDLER_DIRS ${dir})
endforeach()
list(REMOVE_DUPLICATES HANDLER_DIRS)

target_include_directories(Tic_Tac_Toe_Boost PRIVATE
        ${HANDLER_DIRS}
        ${CMAKE_SOURCE_DIR}/src/handlers
        ${CMAKE_SOURCE_DIR}/src/services
        ${CMAKE_SOURCE_DIR}/src/utils
        ${CMAKE_SOURCE_DIR}/src/session
        ${CMAKE_SOURCE_DIR}/src/session_manager
        ${CMAKE_SOURCE_DIR}/src/tcp_server
        ${CMAKE_SOURCE_DIR}/src/routes
        ${CMAKE_SOURCE_DIR}/src/repositories
)

# <----------------------------- Add Boost Asio and Boost.Log ----------------------------->
find_package(Boost REQUIRED COMPONENTS system thread log)
target_include_directories(Tic_Tac_Toe_Boost PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(Tic_Tac_Toe_Boost PRIVATE ${Boost_LIBRARIES})

# <---------------------------- Add Hiredis Dependency ---------------------------->
find_path(HIREDIS_HEADER hiredis)
target_include_directories(Tic_Tac_Toe_Boost PUBLIC ${HIREDIS_HEADER})

find_library(HIREDIS_LIB hiredis)
target_link_libraries(Tic_Tac_Toe_Boost PRIVATE ${HIREDIS_LIB})

# <---------------------- Add Redis-plus-plus Dependency ---------------------->
find_path(REDIS_PLUS_PLUS_HEADER sw)
target_include_directories(Tic_Tac_Toe_Boost PUBLIC ${REDIS_PLUS_PLUS_HEADER})

find_library(REDIS_PLUS_PLUS_LIB redis++)
target_link_libraries(Tic_Tac_Toe_Boost PRIVATE ${REDIS_PLUS_PLUS_LIB})

# <----------------------------- Add External Libraries ----------------------------->
include(FetchContent)

FetchContent_Declare(
        jwt-cpp
        GIT_REPOSITORY https://github.com/Thalhammer/jwt-cpp.git
        GIT_TAG        master
)
FetchContent_MakeAvailable(jwt-cpp)

FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG        v3.10.5
)
FetchContent_MakeAvailable(nlohmann_json)

target_link_libraries(Tic_Tac_Toe_Boost PRIVATE jwt-cpp nlohmann_json::nlohmann_json)