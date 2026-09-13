#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <variant>

class JsonValue;

using JsonObject = std::unordered_map<std::string, JsonValue>;
using JsonArray = std::vector<JsonValue>;

class JsonValue {
public:
    using ValueType = std::variant<std::nullptr_t, bool, double, std::string, JsonObject, JsonArray>;

    JsonValue() : value(nullptr){};
    JsonValue(std::string v) : value(std::move(v)) {};
    JsonValue(double v) : value(v) {};
    JsonValue(bool v) : value(v) {};
    JsonValue(JsonObject v) : value(std::move(v)) {};
    JsonValue(JsonArray v) : value(std::move(v)) {};
private:
    ValueType value;
};
