#include <http_response.h>
#include <sstream>

HttpResponse::HttpResponse(int status) : status_code(status) {
    headers["Content-Type"] = "text/plain";
}

void HttpResponse::set_status(int code) {
    status_code = code;
}

void HttpResponse::set_header(const std::string &key, const std::string &value) {
    headers[key] = value;
}

void HttpResponse::set_body(const std::string &body) {
    response_body = body;
    headers["Content-Length"] = std::to_string(body.size());
}

std::string HttpResponse::to_string() const {
    std::ostringstream response;
    response << "HTTP/1.1 " << status_code << " " << get_status_message() << "\r\n";
    for (const auto &[key, value]: headers) {
        response << key << ": " << value << "\r\n";
    }
    response << "\r\n" << response_body;
    return response.str();
}

std::string HttpResponse::get_status_message() const {
    switch (status_code) {
        case 200: return "OK";
        case 400: return "Bad Request";
        case 401: return "Unauthorized";
        case 403: return "Forbidden";
        case 404: return "Not Found";
        case 500: return "Internal Server Error";
        default: return "Unknown";
    }
}
