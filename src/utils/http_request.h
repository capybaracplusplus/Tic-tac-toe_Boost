#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

struct Json {
    Json(std::string body) : ss(body) {
        boost::property_tree::read_json(ss, pt);
    }

    std::string get(const std::string &req) const {
        return pt.get<std::string>(req);
    }

    std::stringstream ss;
    boost::property_tree::ptree pt;
};

struct http_request {
    std::string uuid;
    std::string method;
    std::string path;
    std::string version;
    Json headers;
    Json body;
};

http_request process_request(std::string &&request);

#endif //HTTPREQUEST_H
