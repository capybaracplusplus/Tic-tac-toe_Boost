include(FetchContent)

FetchContent_Declare(
        jwt-cpp
        GIT_REPOSITORY https://github.com/Thalhammer/jwt-cpp.git
        GIT_TAG master
)

FetchContent_MakeAvailable(jwt-cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE jwt-cpp)