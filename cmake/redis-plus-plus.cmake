cmake_minimum_required(VERSION 3.28)
cmake_policy(SET CMP0167 OLD)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

include(FetchContent)

FetchContent_Declare(
        hiredis
        GIT_REPOSITORY https://github.com/redis/hiredis.git
        GIT_TAG v1.0.2
)

FetchContent_MakeAvailable(hiredis)

FetchContent_Declare(
        redis-plus-plus
        GIT_REPOSITORY https://github.com/sewenew/redis-plus-plus.git
        GIT_TAG 1.3.9
)

FetchContent_MakeAvailable(redis-plus-plus)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${hiredis_SOURCE_DIR}
        ${hiredis_BINARY_DIR}
        ${redis-plus-plus_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME} PRIVATE hiredis redis++)