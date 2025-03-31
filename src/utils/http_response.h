#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include <string>
#include <unordered_map>

class HttpResponse {
public:
  explicit HttpResponse(int status = 200);

  void set_status(int code);

  void set_header(const std::string &key, const std::string &value);

  void set_body(const std::string &body);

  std::string to_string() const;

private:
  int status_code;
  std::unordered_map<std::string, std::string> headers;
  std::string response_body;

  std::string get_status_message() const;
};

#endif // HTTP_RESPONSE_H
