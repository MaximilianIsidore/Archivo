#pragma once

#include <cstddef>
#include <filesystem>
#include <fstream>
#include "JsonValue.hpp"

namespace fs = std::filesystem;


struct fileInfo{
    fs::path fileName;
    size_t fileSize;
};

class JsonParser{

    public:

    // Load json file from filepath
    // asserts whether file extention is .json
    // @return bool
    bool loadJson(const fs::path& filePath);
    JsonValue parseJson();

    private:

    std::ifstream file_;
    std::string content{};

    
    size_t current{0};

    std::string numbers = "0123456789.";

    private:

    //JsonValue parse_value();
    std::string parse_string();
    JsonValue parse_number();
    JsonValue parse_bool();
    JsonValue parse_array();
    JsonValue parse_object();
    JsonValue parse_null();

    //helper functions
    void expect(char c, const std::string& message);
    void advance();
    void skip_whitespaces();

    bool isNumberStart();
};