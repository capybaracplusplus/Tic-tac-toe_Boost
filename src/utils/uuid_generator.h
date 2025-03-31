#ifndef GENERATE_UUID_H
#define GENERATE_UUID_H

#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <string>

namespace utils {
inline std::string generate_uuid() {
  boost::uuids::random_generator generator;
  boost::uuids::uuid uuid = generator();
  return boost::uuids::to_string(uuid);
}
} // namespace utils

#endif // GENERATE_UUID_H
