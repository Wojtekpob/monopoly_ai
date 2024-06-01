#ifndef UTILITYFIELD_H
#define UTILITYFIELD_H

#include "Property.h"

class UtilityField : public Property {
public:
    UtilityField(int id, const std::string& name, sf::Color& color, std::shared_ptr<TextRenderer> textRenderer, int cost, int rent);

    void invokeAction(std::shared_ptr<Player> player) override;
    bool isActionAvailable(std::shared_ptr<Player> player, Action action) override;
    int getRent();
    std::string getStr(Action action) override;
    void nextRound() override {};

private:
    int rent_;
};

#endif // UTILITYFIELD_H
