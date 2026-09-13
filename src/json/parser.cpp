
#include "json/parser.hpp"
#include <stdexcept>
#include <cctype>


bool JsonParser::loadJson(const fs::path& filePath){

    if(!fs::exists(filePath)){
        throw std::runtime_error("file does not exist");
    }

    if(!fs::is_regular_file(filePath)){
        throw std::runtime_error("Not a file");
    }

    if(filePath.extension()  != ".json"){
        throw std::runtime_error("Not a json file");
    }

    file_.open(filePath);

    if(!file_.is_open()){
        throw std::runtime_error("file cannot be opened");
    }


    std::string line{};

    while(std::getline(file_, line)){
        content += line + "\n";
    }
    content += '\0';

    return true;
}

JsonValue JsonParser::parseJson(){

    JsonValue v;
    while(content[current] != '\0'){

        skip_whitespaces();
        switch (content[current])
        {
            case '{':
                return parse_object();
                break;
            case '[':
                return parse_array();
                break;
            case '"':
                return JsonValue(parse_string());
                break;
            case 't':
                return parse_bool();
                break;
            case 'f':
                return parse_bool();
                break;
            case 'n':
                return parse_null();
                break;        
            default:
                if(isNumberStart())
                    return parse_number();
                throw std::runtime_error("Invalid type");
        }
        skip_whitespaces();
    }

    return v;
}

void JsonParser::advance(){
    if(content[current+1] != '\0')
        current++;
}

void JsonParser::expect(char c, const std::string& message){
    if(content[current] != c){
        throw std::runtime_error(message);
    }

    advance();
}

void JsonParser::skip_whitespaces(){

    while(std::isspace(static_cast<unsigned char>(content[current]))){
        advance();
    }
}

JsonValue JsonParser::parse_null(){
    if("null" == content.substr(current, 4)){
        current += 4;
        return JsonValue();
    }

    throw std::runtime_error("Expected null");
}

JsonValue JsonParser::parse_bool(){

    if("true" == content.substr(current,4)){
        current += 4;
        return JsonValue(true);
    }

    if("false" == content.substr(current,5)){
        current += 5;
        return JsonValue(false);
    }

    throw std::runtime_error("Expected bool value");
}

std::string JsonParser::parse_string(){
    advance();

    std::string s;

    while(content[current] != '"'){
        s += content[current];
        advance();
    }
    expect('"', "Expected '\"' at end of the string");

    return s;
}

bool JsonParser::isNumberStart(){
    if(numbers.find(content[current]) != std::string::npos){
        return true;
    }

    return false;
}

JsonValue JsonParser::parse_number(){
    int i = current;

    while(numbers.find(content[i]) != std::string::npos)
    {   
        i++;
    }

    double num = std::stod(content.substr(current, (i-current)));
    current = i;

    return JsonValue(num);
}

JsonValue JsonParser::parse_array(){
    advance();
    JsonArray jsonarray;

    skip_whitespaces();

    auto value = parseJson();
    jsonarray.push_back(value);

    skip_whitespaces();

    while(content[current] == ','){
        advance();
        skip_whitespaces();

        auto value = parseJson();
        jsonarray.push_back(value);

        skip_whitespaces();
    }

    expect(']', "expected ] at end of array");

    return JsonValue(std::move(jsonarray));
}

JsonValue JsonParser::parse_object(){
    advance();

    JsonObject jsonobject;

    skip_whitespaces();
    std::string key = parse_string();
    skip_whitespaces();

    expect(':', "expected : in object");
    
    skip_whitespaces();
    auto value = parseJson();
    skip_whitespaces();

    auto [it, inserted] = jsonobject.emplace(std::move(key), std::move(value));

    if (!inserted) {
        throw std::runtime_error("Duplicate key");
    }

    while(content[current] == ','){
        advance();
        skip_whitespaces();
        std::string key = parse_string();
        skip_whitespaces();

        expect(':', "expected : in object");
        
        skip_whitespaces();
        auto value = parseJson();
        skip_whitespaces();

        auto [it, inserted] = jsonobject.emplace(std::move(key), std::move(value));

        if (!inserted) {
            throw std::runtime_error("Duplicate key");
        }
    }

    expect('}', "expected } at objects end");

    return JsonValue(std::move(jsonobject));
}