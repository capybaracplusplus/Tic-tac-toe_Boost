cmake_minimum_required(VERSION 3.28)
cmake_policy(SET CMP0167 OLD)
project(Tic_Tac_Toe_Boost)

set(CMAKE_CXX_STANDARD 23)

add_executable(Tic_Tac_Toe_Boost src/main.cpp
        src/services/Service.h
        src/utils/generate_uuid.h
        src/tcp_server/server.h
        src/handlers/handler.h
        src/handlers/get_id_handler.h
        src/handlers/NotFoundHandler.h
        src/handlers/handlers.h
        src/utils/HttpRequest.h
        src/routes/router.h
        src/tcp_server/server.cpp
        src/handlers/main_handler.h
        src/repositories/Redis_repos.cpp
        src/repositories/Redis_repos.h
        src/services/service.cpp
        src/utils/jwtToken.h)

target_include_directories(Tic_Tac_Toe_Boost PRIVATE
        ${CMAKE_SOURCE_DIR}/src/handlers
        ${CMAKE_SOURCE_DIR}/src/services
        ${CMAKE_SOURCE_DIR}/src/utils
        ${CMAKE_SOURCE_DIR}/src/tcp_server
        ${CMAKE_SOURCE_DIR}/src/routes
        ${CMAKE_SOURCE_DIR}/src/repositories
)

# <------------ add Boost asio --------------->
find_package(Boost REQUIRED COMPONENTS system thread)
target_include_directories(Tic_Tac_Toe_Boost PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(Tic_Tac_Toe_Boost PRIVATE ${Boost_LIBRARIES})


# <------------ add hiredis dependency --------------->
find_path(HIREDIS_HEADER hiredis)
target_include_directories(Tic_Tac_Toe_Boost PUBLIC ${HIREDIS_HEADER})

find_library(HIREDIS_LIB hiredis)
target_link_libraries(Tic_Tac_Toe_Boost PRIVATE ${HIREDIS_LIB})

# <------------ add redis-plus-plus dependency -------------->
# NOTE: this should be *sw* NOT *redis++*
find_path(REDIS_PLUS_PLUS_HEADER sw)
target_include_directories(Tic_Tac_Toe_Boost PUBLIC ${REDIS_PLUS_PLUS_HEADER})

find_library(REDIS_PLUS_PLUS_LIB redis++)
target_link_libraries(Tic_Tac_Toe_Boost PRIVATE ${REDIS_PLUS_PLUS_LIB})

# <------------ add cpp-jwt -------------->
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

target_link_libraries(Tic_Tac_Toe_Boost PRIVATE jwt-cpp)
target_link_libraries(Tic_Tac_Toe_Boost PRIVATE nlohmann_json::nlohmann_json)
