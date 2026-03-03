#ifndef PISHTTP_HTTPUTIL_H
#define PISHTTP_HTTPUTIL_H
#include <nlohmann/json.hpp>

#pragma once
using namespace Pistache;
using json = nlohmann::json;

// 工具函数
std::string getTimestamp();

void sendJsonResponse(Http::Code code, const json& data, Http::ResponseWriter& response);

void sendErrorResponse(Http::Code code, const std::string& message, Http::ResponseWriter& response);

void sendNotFound(Http::ResponseWriter& response);

void sendResponse(Http::ResponseWriter& response, const std::string& data);         

int getOptionalInt(json jsonData, std::string itemName);

std::string getOptionalString(json jsonData, std::string itemName);

std::string urlDecode(const std::string& input);

std::string boolToStr(bool input);

#endif //PISHTTP_HTTPUTIL_H
