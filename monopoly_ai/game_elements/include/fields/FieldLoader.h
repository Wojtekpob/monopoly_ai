#ifndef FIELDLOADER_H
#define FIELDLOADER_H

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

using json = nlohmann::json;

class FieldLoader {
public:
    std::vector<std::shared_ptr<ActionField>> loadFields(const std::string& jsonString);
    std::shared_ptr<ActionField> loadField(const json& j, int id);

private:
    std::shared_ptr<Estate> createEstate(const json& j, int id);
    std::shared_ptr<BlankField> createBlankField(const json& j, int id);
    std::shared_ptr<TaxField> createTaxField(const json& j, int id);
    std::shared_ptr<UtilityField> createUtilityField(const json& j, int id);
    std::shared_ptr<GoToJailField> createGoToJailField(const json& j, int id);
    std::shared_ptr<RailRoad> createRailRoad(const json& j, int id);

    static int id_count_;
};

#endif // FIELDLOADER_H
