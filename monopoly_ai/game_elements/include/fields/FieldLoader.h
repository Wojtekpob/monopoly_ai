/*
 * This file defines the FieldLoader class, responsible for loading game fields from a JSON configuration file.
 * The FieldLoader class uses the nlohmann::json library to parse the JSON file and creates instances of various
 * field types such as Estate, BlankField, TaxField, UtilityField, GoToJailField, and RailRoad.
 * It includes methods to load all fields from a JSON file, load an individual field, and create specific types
 * of fields based on the parsed JSON data.
 * Author: Wojciech Pobocha
 */

#ifndef FIELDLOADER_H
#define FIELDLOADER_H

#include <string>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "fields/ActionField.h"
#include "fields/Estate.h"
#include "nlohmann/json.hpp"
#include "fields/BlankField.h"
#include "fields/TaxField.h"
#include "fields/UtilityField.h"
#include "fields/GoToJailField.h"
#include "fields/RailRoad.h"
#include "TextRenderer.h"

using json = nlohmann::json;

class FieldLoader {
public:
    FieldLoader(std::shared_ptr<TextRenderer> textRenderer);
    std::vector<std::shared_ptr<ActionField>> loadFields(const std::string& jsonString);
    std::shared_ptr<ActionField> loadField(const json& j, int id);

private:
    std::shared_ptr<Estate> createEstate(const json& j, int id, sf::Color& color);
    std::shared_ptr<BlankField> createBlankField(const json& j, int id, sf::Color& color);
    std::shared_ptr<TaxField> createTaxField(const json& j, int id, sf::Color& color);
    std::shared_ptr<UtilityField> createUtilityField(const json& j, int id, sf::Color& color);
    std::shared_ptr<GoToJailField> createGoToJailField(const json& j, int id, sf::Color& color);
    std::shared_ptr<RailRoad> createRailRoad(const json& j, int id, sf::Color& color);

    std::shared_ptr<TextRenderer> textRenderer_;
    static int id_count_;
};

#endif // FIELDLOADER_H
