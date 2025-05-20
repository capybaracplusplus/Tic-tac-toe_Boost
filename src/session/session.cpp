#include <boost/asio/read_until.hpp>
#include <boost/log/trivial.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <session/session.h>
using json = nlohmann::json;

router Session::router_;

Session::Session(boost::asio::io_context &io_context, tcp::socket socket)
    : socket_(std::move(socket)), io_context_(io_context) {}

void Session::start() { read_request(); }

void Session::set_uuid(std::string uuid) { uuid_ = uuid; }

http_request process_headers(const std::string &raw_headers) {
  http_request parsed_request;
  std::istringstream stream(raw_headers);
  std::string line;

  if (std::getline(stream, line)) {
    std::istringstream line_stream(line);
    line_stream >> parsed_request.method >> parsed_request.path >>
        parsed_request.version;
  }

  while (std::getline(stream, line)) {
    size_t pos = line.find(':');
    if (pos != std::string::npos) {
      std::string key = line.substr(0, pos);
      std::string value = line.substr(pos + 1);
      while (!value.empty() && value.front() == ' ')
        value.erase(value.begin());
      parsed_request.headers[key] = value;
    }
  }

  return parsed_request;
}

void Session::read_request() {
  auto self = shared_from_this();

  boost::asio::async_read_until(
      socket_, buffer_, "\r\n\r\n",
      [this, self](boost::system::error_code ec, std::size_t header_length) {
        if (ec) {
          if (ec == boost::asio::error::eof) {
            BOOST_LOG_TRIVIAL(info) << "Connection closed by client (EOF).";
          } else {
            BOOST_LOG_TRIVIAL(error) << "Header read error: " << ec.message();
          }
          return;
        }

        std::istream stream(&buffer_);
        std::string headers_str(header_length, '\0');
        stream.read(&headers_str[0], header_length);

        http_request req = process_headers(headers_str);
        req.uuid = uuid_;

        std::size_t content_length = 0;
        if (req.headers.count("Content-Length")) {
          content_length = std::stoul(req.headers["Content-Length"]);
        }

        // Уже могли быть байты тела в буфере
        std::string remaining((std::istreambuf_iterator<char>(stream)), {});
        std::size_t already_read = remaining.size();

        if (already_read >= content_length) {
          std::string body_str = remaining.substr(0, content_length);
          std::string trimmed = body_str;
          trimmed.erase(
              std::remove_if(trimmed.begin(), trimmed.end(), ::isspace),
              trimmed.end());

          if (!trimmed.empty()) {
            try {
              req.body = json::parse(body_str);
            } catch (const json::parse_error &e) {
              BOOST_LOG_TRIVIAL(error)
                  << "JSON parse error (partial body): " << e.what();
              req.body = json::object();
            }
          } else {
            req.body = json::object();
          }

          router_.route_request(io_context_, socket_, std::move(req));
          read_request();
        } else {
          // дочитываем оставшееся тело
          boost::asio::async_read(
              socket_, buffer_,
              boost::asio::transfer_exactly(content_length - already_read),
              [this, self, req = std::move(req),
               remaining = std::move(remaining)](boost::system::error_code ec,
                                                 std::size_t) mutable {
                if (ec) {
                  BOOST_LOG_TRIVIAL(error)
                      << "Body read error: " << ec.message();
                  return;
                }

                std::istream body_stream(&buffer_);
                std::string extra((std::istreambuf_iterator<char>(body_stream)),
                                  {});
                std::string full_body = remaining + extra;

                std::string trimmed = full_body;
                trimmed.erase(
                    std::remove_if(trimmed.begin(), trimmed.end(), ::isspace),
                    trimmed.end());

                if (!trimmed.empty()) {
                  try {
                    req.body = json::parse(full_body);
                  } catch (const json::parse_error &e) {
                    BOOST_LOG_TRIVIAL(error)
                        << "JSON parse error (full body): " << e.what();
                    req.body = json::object();
                  }
                } else {
                  req.body = json::object();
                }

                router_.route_request(io_context_, socket_, std::move(req));
                read_request();
              });
        }
      });
}
