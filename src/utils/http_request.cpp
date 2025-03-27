#include <http_request.h>
#include <unordered_map>
#include <string>
#include <sstream>

http_request process_request(std::string &&request) {
    http_request parsed;
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
    if (auto it = parsed.headers.find("Content-Length"); it != parsed.headers.end()) {
        size_t content_length = std::stoul(it->second);
        parsed.body.resize(content_length);
        request_stream.read(&parsed.body[0], content_length);
    }

    return std::move(parsed);
}
