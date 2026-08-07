
#include "json/parser.hpp"
#include <stdexcept>

bool JsonParser::loadJson(const fs::path& filePath){

    if(!fs::exists(filePath)){
        throw std::runtime_error("file does not exist");
    }

    if(!fs::is_regular_file(filePath)){
        throw std::runtime_error("Not a file");
    }

    if(path.extention()  != ".json"){
        throw std::runtime_error("Not a json file");
    }

    file_.open(path);

    if(!file_.is_open()){
        throw std::runtime_error("file cannot be opened");
    }

    return true;
}