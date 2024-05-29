#include "Color.h"

const sf::Color Color::Black = sf::Color::Black;
const sf::Color Color::White = sf::Color::White;
const sf::Color Color::Red = sf::Color::Red;
const sf::Color Color::Green = sf::Color::Green;
const sf::Color Color::Blue = sf::Color::Blue;
const sf::Color Color::Yellow = sf::Color::Yellow;
const sf::Color Color::Magenta = sf::Color::Magenta;
const sf::Color Color::Cyan = sf::Color::Cyan;
const sf::Color Color::Transparent = sf::Color::Transparent;

const sf::Color Color::Brown = sf::Color(139, 69, 19);
const sf::Color Color::LightBlue = sf::Color(173, 216, 230);
const sf::Color Color::Pink = sf::Color(255, 192, 203);
const sf::Color Color::Orange = sf::Color(255, 165, 0);
const sf::Color Color::DarkRed = sf::Color(139, 0, 0);
const sf::Color Color::DarkYellow = sf::Color(204, 204, 0);
const sf::Color Color::DarkGreen = sf::Color(0, 100, 0);
const sf::Color Color::DarkBlue = sf::Color(0, 0, 139);

std::unordered_map<std::string, sf::Color> Color::colorMap = {
    {"Black", Color::Black},
    {"White", Color::White},
    {"Red", Color::Red},
    {"Green", Color::Green},
    {"Blue", Color::Blue},
    {"Yellow", Color::Yellow},
    {"Magenta", Color::Magenta},
    {"Cyan", Color::Cyan},
    {"Transparent", Color::Transparent},
    {"Brown", Color::Brown},
    {"LightBlue", Color::LightBlue},
    {"Pink", Color::Pink},
    {"Orange", Color::Orange},
    {"DarkRed", Color::DarkRed},
    {"DarkYellow", Color::DarkYellow},
    {"DarkGreen", Color::DarkGreen},
    {"DarkBlue", Color::DarkBlue},
    {"Gray", sf::Color(128, 128, 128)},
    {"LightGray", sf::Color(211, 211, 211)}
};

sf::Color Color::getColor(const std::string& name) {
    auto it = colorMap.find(name);
    if (it != colorMap.end()) {
        return it->second;
    }
    throw std::invalid_argument("Unknown color name: " + name);
}
