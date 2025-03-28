#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <unordered_map>
#include <string>

struct http_request {
    std::string uuid;
    std::string method;
    std::string path;
    std::string version;
    std::unordered_map<std::string, std::string> headers;
    std::string body;
};

http_request process_request(std::string &&request);

#endif //HTTPREQUEST_H
