#ifndef JWTTOKEN_H
#define JWTTOKEN_H

#include <jwt-cpp/jwt.h>
#include <string>
#include <chrono>

namespace utils {
    class JWTToken {
    public:
        JWTToken(const std::string &secretKey = "secretkey",
                 std::size_t accessTokenLifetimeMinutes = 60) : secretKey_(secretKey),
                                                                accessTokenLifetime_(
                                                                    std::chrono::minutes(accessTokenLifetimeMinutes)) {
        }

        std::string create() {
            auto now = std::chrono::system_clock::now();
            std::string accessToken = jwt::create()
                    .set_issuer("Capy")
                    .set_issued_at(now)
                    .set_expires_at(now + accessTokenLifetime_)
                    .sign(jwt::algorithm::hs256{secretKey_});
            return accessToken;
        }

        bool validateToken(const std::string &token) const try {
            auto decodedToken = jwt::decode(token);

            jwt::verify()
                    .allow_algorithm(jwt::algorithm::hs256{secretKey_})
                    .with_issuer("Capy")
                    .verify(decodedToken);
            return true;
        } catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return false;
        }

    private:
        std::string accessToken;

    private:
        std::string secretKey_;
        std::chrono::system_clock::duration accessTokenLifetime_;
    };
}


#endif //JWTTOKEN_H
