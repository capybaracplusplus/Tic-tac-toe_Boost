cmake_minimum_required(VERSION 3.28)
cmake_policy(SET CMP0167 OLD)
project(Tic_Tac_Toe_Boost)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# <----------------------------- Add Executable ----------------------------->
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*.h)
add_executable(${PROJECT_NAME} ${SRC_FILES}
        src/utils/redis_client_factory.h
        src/utils/redis_client_factory.cpp)

# <---------------------------- Include Directories ---------------------------->
file(GLOB_RECURSE HANDLER_HEADERS ${CMAKE_SOURCE_DIR}/src/handlers/*.h)

set(HANDLER_DIRS "")
foreach(header ${HANDLER_HEADERS})
    get_filename_component(dir ${header} DIRECTORY)
    list(APPEND HANDLER_DIRS ${dir})
endforeach()
list(REMOVE_DUPLICATES HANDLER_DIRS)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${HANDLER_DIRS}
        ${CMAKE_SOURCE_DIR}/src
)

# <----------------------------- Add External Libraries ----------------------------->
include(cmake/jwt-cpp.cmake)
include(cmake/nlohmann_json.cmake)
include(cmake/redis-plus-plus.cmake)
include(cmake/boost.cmake)