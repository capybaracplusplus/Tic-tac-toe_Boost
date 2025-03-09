#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <unordered_map>
#include <string>
#include <sstream>

struct HttpRequest {
    std::string method;
    std::string path;
    std::string version;
    std::unordered_map<std::string, std::string> headers;
    std::string body;
};

inline HttpRequest process_request(std::string &&request) {
    HttpRequest parsed;
    std::istringstream request_stream(request);
    std::string line;

    // "POST /move HTTP/1.1"
    if (std::getline(request_stream, line)) {
        std::istringstream line_stream(line);
        line_stream >> parsed.method >> parsed.path >> parsed.version;
    }

    while (std::getline(request_stream, line) && line != "\r") {
        size_t pos = line.find(": ");
        if (pos != std::string::npos) {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 2);
            parsed.headers[key] = value;
        }
    }
    // body
    auto it = parsed.headers.find("Content-Length");
    if (it != parsed.headers.end()) {
        size_t content_length = std::stoul(it->second);
        parsed.body.resize(content_length);
        request_stream.read(&parsed.body[0], content_length);
    }

    return std::move(parsed);
}


#endif //HTTPREQUEST_H
