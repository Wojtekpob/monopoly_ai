#include "fields/FieldLoader.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <string>
#include "Color.h"

std::vector<std::shared_ptr<ActionField>> FieldLoader::loadFields(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    json j;
    file >> j;
    int id = 0;
    std::vector<std::shared_ptr<ActionField>> fields;
    for (const auto& fieldJson : j["fields"]) {
        fields.push_back(loadField(fieldJson, id));
        ++id;
    }

    return fields;
}

std::shared_ptr<ActionField> FieldLoader::loadField(const json& j, int id) {
    std::string type = j.value("type", "");
    sf::Color color = Color::getColor(j.value("color", ""));

    if (type == "Estate") {
        return createEstate(j, id, color);
    }
    else if (type == "BlankField") {
        return createBlankField(j, id, color);
    }
    else if (type == "TaxField") {
        return createTaxField(j, id, color);
    }
    else if (type == "UtilityField") {
        return createUtilityField(j, id, color);
    }
    else if (type == "GoToJailField") {
        return createGoToJailField(j, id, color);
    }
    else if (type == "RailRoad") {
        return createRailRoad(j, id, color);
    }
    else {
        throw std::runtime_error("Unknown field type: " + type);
    }
}

std::shared_ptr<Estate> FieldLoader::createEstate(const json& j, int id, sf::Color& color) {
    std::string name = j.value("name", "");
    std::string province = j.value("province", "");
    int cost = j.value("cost", 0);
    int houseCost = j.value("house_cost", 0);
    int hotelCost = j.value("hotel_cost", 0);
    std::vector<int> houses_rent = j.value("houses_rent", std::vector<int>{0, 0, 0, 0, 0, 0});
    return std::make_shared<Estate>(id, name, color, cost, houseCost, hotelCost, houses_rent, province);
}

std::shared_ptr<BlankField> FieldLoader::createBlankField(const json& j, int id, sf::Color& color) {
    std::string name = j.value("name", "");
    return std::make_shared<BlankField>(id, name, color);
}

std::shared_ptr<TaxField> FieldLoader::createTaxField(const json& j, int id, sf::Color& color) {
    std::string name = j.value("name", "");
    int taxAmount = j.value("tax_amount", 0);
    return std::make_shared<TaxField>(id, name, color, taxAmount);
}

std::shared_ptr<UtilityField> FieldLoader::createUtilityField(const json& j, int id, sf::Color& color) {
    std::string name = j.value("name", "");
    int cost = j.value("cost", 0);
    int rent = j.value("rent", 0);
    return std::make_shared<UtilityField>(id, name, color, cost, rent);
}

std::shared_ptr<GoToJailField> FieldLoader::createGoToJailField(const json& j, int id, sf::Color& color) {
    std::string name = j.value("name", "");
    return std::make_shared<GoToJailField>(id, name, color);
}

std::shared_ptr<RailRoad> FieldLoader::createRailRoad(const json& j, int id, sf::Color& color) {
    std::string name = j.value("name", "");
    int cost = j.value("cost", 0);
    int rent = j.value("rent", 0);
    return std::make_shared<RailRoad>(id, name, color, cost, rent);
}