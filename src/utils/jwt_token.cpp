#include <jwt_token.h>

namespace utils {
    std::string JWTToken::create() noexcept {
        auto now = std::chrono::system_clock::now();
        accessToken_ = jwt::create()
                .set_issuer("Capy")
                .set_issued_at(now)
                .set_expires_at(now + accessTokenLifetime_)
                .sign(jwt::algorithm::hs256{secretKey_});
        return accessToken_;
    }

    void JWTToken::validateToken(const std::string &token) const noexcept(false) {
        auto decodedToken = jwt::decode(token);

        jwt::verify()
                .allow_algorithm(jwt::algorithm::hs256{secretKey_})
                .with_issuer("Capy")
                .verify(decodedToken);
    }
}
