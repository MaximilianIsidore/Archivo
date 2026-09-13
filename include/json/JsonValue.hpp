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

    bool isString() const { return std::holds_alternative<std::string>(value); }
    bool isNumber() const { return std::holds_alternative<double>(value); }
    bool isBool() const { return std::holds_alternative<bool>(value); }
    bool isNull() const { return std::holds_alternative<std::nullptr_t>(value); }
    bool isArray() const { return std::holds_alternative<JsonArray>(value); }
    bool isObject() const { return std::holds_alternative<JsonObject>(value); }

    // Getters 
    const std::string& getString() const { return std::get<std::string>(value); }
    double getNumber() const { return std::get<double>(value); }
    bool getBool() const { return std::get<bool>(value); }
    const JsonArray& getArray() const { return std::get<JsonArray>(value); }
    const JsonObject& getObject() const { return std::get<JsonObject>(value); }
private:
    ValueType value;
};
