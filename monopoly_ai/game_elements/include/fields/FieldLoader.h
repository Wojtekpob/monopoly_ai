#ifndef FIELDLOADER_H
#define FIELDLOADER_H

#include <string>
#include <vector>
#include <memory>
#include "fields/ActionField.h"
#include "fields/Property.h"
#include "fields/Estate.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class FieldLoader {
public:
    std::vector<std::shared_ptr<ActionField>> loadFields(const std::string& jsonString);
    std::shared_ptr<ActionField> loadField(const json& j);

private:
    std::shared_ptr<Estate> createEstate(const json& j, int id);

};

#endif // FIELDLOADER_H
