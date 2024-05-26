#include "fields/FieldLoader.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <string>

std::vector<std::shared_ptr<ActionField>> FieldLoader::loadFields(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    json j;
    file >> j;

    std::vector<std::shared_ptr<ActionField>> fields;
    for (const auto& fieldJson : j["fields"]) {
        fields.push_back(loadField(fieldJson));
    }

    return fields;
}
std::shared_ptr<ActionField> FieldLoader::loadField(const json& j) {
    //int id = j.value("id", 0);
    std::string type = j.value("type", "");

    if (type == "Estate") {
        return createEstate(j, 0); // @TODO to change
    }
    // Add other types here
    else {
        throw std::runtime_error("Unknown field type: " + type);
    }
}

std::shared_ptr<Estate> FieldLoader::createEstate(const json& j, int id) {
    std::string name = j.value("province", "");
    int cost = j.value("cost", 0);
    int houseCost = j.value("house_cost", 0);
    int hotelCost = j.value("hotel_cost", 0);
    std::vector<int> houses_rent = j.value("houses_rent", std::vector<int>{0, 0, 0, 0, 0, 0});
    return std::make_shared<Estate>(id, name, cost, houseCost, hotelCost, houses_rent);
}

