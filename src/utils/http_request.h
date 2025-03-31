#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>
using Json = nlohmann::json;

struct http_request {
  std::string uuid;
  std::string method;
  std::string path;
  std::string version;
  std::unordered_map<std::string, std::string> headers;
  Json body;
};

http_request process_request(std::string &&request);

#endif // HTTPREQUEST_H
