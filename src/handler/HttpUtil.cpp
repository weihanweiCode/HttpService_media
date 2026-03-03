#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <nlohmann/json.hpp>
#include "handler/HttpUtil.h"

using namespace Pistache;
using json = nlohmann::json;


// 工具函数
std::string getTimestamp() {
    auto now = std::chrono::system_clock::now();
    return "---time---";
}

void sendJsonResponse(Http::Code code, const json& data, Http::ResponseWriter& response) {
    response.headers().add<Http::Header::ContentType>(MIME(Application,  Json));
    response.send(code,  data.dump());
}

void sendErrorResponse(Http::Code code, const std::string& message, Http::ResponseWriter& response) {
    json res = {{"error", message}, {"code", static_cast<int>(code)}};
    sendJsonResponse(code, res, response);
}

void sendNotFound(Http::ResponseWriter& response) {
    json res = {{"error", "Endpoint not found"}, {"suggestion", "/health, /user/:id, /data"}};
    sendJsonResponse(Http::Code::Not_Found, res, response);
}

void sendResponse(Http::ResponseWriter& response, const std::string& data) { 
    response.headers().add<Http::Header::ContentType>(MIME(Application,  Json)); 
    response.send(Http::Code::Ok,  data); 
} 

int getOptionalInt(json jsonData, std::string itemName){
    int optionalField;
    if (jsonData.contains(itemName)) {
        if (!jsonData[itemName].is_null()) {
            optionalField = jsonData[itemName].get<int>();
        }
    }
    return optionalField;
}

std::string getOptionalString(json jsonData, std::string itemName){
    std::string optionalField;
    if (jsonData.contains(itemName)) {
        if (!jsonData[itemName].is_null()) {
            optionalField = jsonData[itemName].get<std::string>();
        }
    }    
    return optionalField;
}

std::string urlDecode(const std::string& input) {
    std::stringstream output;
    for (size_t i = 0; i < input.length(); ++i) {
        if (input[i] == '%') {
            if (i + 2 < input.length()) {
                std::string hex = input.substr(i + 1, 2);
                char c = static_cast<char>(std::stoi(hex, nullptr, 16));
                output << c;
                i += 2;
            }
        } else if (input[i] == '+') {
            output << ' ';
        } else {
            output << input[i];
        }
    }
    return output.str();
}


std::string boolToStr(bool input) {
    return input ? "success" : "fail";
}
