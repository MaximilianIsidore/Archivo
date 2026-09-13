#include <iostream>

#include "json/parser.hpp"

int main(){

    JsonParser parser;

    try{
        if(!parser.loadJson("../sample.json")){
            std::cout<<"unable to open the file\n";
        }

        JsonValue root = parser.parseJson();

        // 2. Get the root object
        JsonObject rootObj = root.getObject();

        // 3. Read basic types
        std::string name = rootObj["name"].getString();
        double age = rootObj["age"].getNumber();
        bool isActive = rootObj["active"].getBool();
        bool isVerified = rootObj["verified"].getBool();

        std::cout<< std::boolalpha;
        std::cout<< "Name: "<<name<<" \n"
                << "Age: "<<age<<" \n"
                <<"Active: "<<isActive<<" \n"
                <<"Verified: "<<isVerified<<std::endl;

        // 4. Read an Array ("skills")
        JsonArray skills = rootObj["skills"].getArray();
        std::cout << "Skills: \n";
        for (const auto& skillVal : skills) {
            std::cout << "- " << skillVal.getString() << "\n";
        }

        // 5. Read a Nested Object ("address")
        JsonObject address = rootObj["address"].getObject();
        std::string city = address["city"].getString();
        double zip = address["zip"].getNumber();

        std::cout<<"city: "<< city <<" \n"
                <<"Pincode: "<< zip <<" \n";
    }
    catch(const std::exception& e){
        std::cout<<"Error happened : "<< e.what() << std::endl;
    }
    return 0;
}