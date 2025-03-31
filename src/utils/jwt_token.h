#ifndef JWTTOKEN_H
#define JWTTOKEN_H

#include <jwt-cpp/jwt.h>
#include <string>

namespace utils {
class JWTToken {
public:
  static std::string create(const std::string &secretKey) noexcept;

  static void validateToken(const std::string &token,
                            const std::string &secretKey) noexcept(false);
};
} // namespace utils

#endif // JWTTOKEN_H
