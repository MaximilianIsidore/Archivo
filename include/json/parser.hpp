#pragma once

#include <cstddef>
#include <filesystem>
#include <fstream>

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

    private:

    std::ifstream file_;

};