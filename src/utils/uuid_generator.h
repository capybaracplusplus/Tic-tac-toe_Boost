#ifndef GENERATE_UUID_H
#define GENERATE_UUID_H

#include <boost/uuid/uuid_io.hpp>
#include<boost/uuid/uuid_generators.hpp>
#include <string>

namespace utils {
    inline std::string generate_uuid() {
        static boost::uuids::random_generator generator;
        boost::uuids::uuid uuid = generator();
        return boost::uuids::to_string(uuid);
    }
}

#endif //GENERATE_UUID_H
