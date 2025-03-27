#ifndef JWTTOKEN_H
#define JWTTOKEN_H

#include <jwt-cpp/jwt.h>
#include <string>
#include <chrono>

namespace utils {
    class JWTToken {
    public:
        JWTToken(const std::string &secretKey = "secretkey",
                 std::size_t accessTokenLifetimeMinutes = 60) noexcept : secretKey_(secretKey),
                                                                         accessTokenLifetime_(
                                                                             std::chrono::minutes(
                                                                                 accessTokenLifetimeMinutes)) {
        }

        std::string create() noexcept;

        void validateToken(const std::string &token) const noexcept(false);

    private:
        std::string accessToken_;
        std::string secretKey_;
        std::chrono::system_clock::duration accessTokenLifetime_;
    };
}


#endif //JWTTOKEN_H
