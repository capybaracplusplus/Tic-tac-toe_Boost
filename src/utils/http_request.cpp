#include <http_request.h>
#include <unordered_map>
#include <string>
#include <sstream>

http_request process_request(std::string &&request) {
    http_request parsed_request;

    // Ищем конец заголовков (`\r\n\r\n` или `\n\n`)
    size_t header_end = request.find("\r\n\r\n");
    size_t delimiter_size = 4; // Размер `\r\n\r\n`

    if (header_end == std::string::npos) {
        header_end = request.find("\n\n");
        delimiter_size = 2; // Размер `\n\n`
    }

    // Если нашли разделитель заголовков и тела
    if (header_end != std::string::npos) {
        std::string body = request.substr(header_end + delimiter_size);
        parsed_request.body = nlohmann::json::parse(body);
    }

    // Берём только заголовочную часть
    std::string headers_part = request.substr(0, header_end);
    std::istringstream stream(headers_part);
    std::string line;

    // Разбираем первую строку (метод, путь, версия)
    if (std::getline(stream, line)) {
        std::istringstream line_stream(line);
        line_stream >> parsed_request.method >> parsed_request.path >> parsed_request.version;
    }

    // Разбираем заголовки
    while (std::getline(stream, line)) {
        size_t pos = line.find(':');
        if (pos != std::string::npos) {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            while (!value.empty() && value.front() == ' ') value.erase(value.begin()); // Убираем пробелы
            parsed_request.headers[key] = value;
        }
    }

    return parsed_request;
}
