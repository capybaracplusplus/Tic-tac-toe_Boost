#ifndef TIC_TAC_TOE_BOOST_CONFLICT_EXCEPTION_H
#define TIC_TAC_TOE_BOOST_CONFLICT_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace exceptions {

class ConflictException : public std::runtime_error {
public:
  explicit ConflictException(
      const std::string &msg =
          "Request could not be completed due to a conflict")
      : std::runtime_error(msg) {}
};
} // namespace exceptions
#endif // TIC_TAC_TOE_BOOST_CONFLICT_EXCEPTION_H
