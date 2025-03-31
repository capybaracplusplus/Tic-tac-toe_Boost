#include <jwt_token.h>
#include <chrono>

namespace utils {
    std::string JWTToken::create(const std::string &secretKey) noexcept {
        auto now = std::chrono::system_clock::now();
        std::size_t accessTokenLifetimeMinutes = 30;
        std::chrono::system_clock::duration accessTokenLifetime = std::chrono::minutes(
            accessTokenLifetimeMinutes);
        std::string accessToken = jwt::create()
                .set_issuer("Capy")
                .set_issued_at(now)
                .set_expires_at(now + accessTokenLifetime)
                .sign(jwt::algorithm::hs256{secretKey});
        return accessToken;
    }

    void JWTToken::validateToken(const std::string &token, const std::string &secretKey) noexcept(false) {
        auto decodedToken = jwt::decode(token);
        jwt::verify()
                .allow_algorithm(jwt::algorithm::hs256{secretKey})
                .with_issuer("Capy")
                .verify(decodedToken);
    }
}
