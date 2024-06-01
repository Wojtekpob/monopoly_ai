#ifndef FIELDLOADER_H
#define FIELDLOADER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <memory>
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
