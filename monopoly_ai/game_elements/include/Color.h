#ifndef COLOR_H
#define COLOR_H

#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>

class Color {
public:
    static sf::Color getColor(const std::string& name);

    static const sf::Color Black;
    static const sf::Color White;
    static const sf::Color Red;
    static const sf::Color Green;
    static const sf::Color Blue;
    static const sf::Color Yellow;
    static const sf::Color Magenta;
    static const sf::Color Cyan;
    static const sf::Color Transparent;

    static const sf::Color Brown;
    static const sf::Color LightBlue;
    static const sf::Color Pink;
    static const sf::Color Orange;
    static const sf::Color DarkRed;
    static const sf::Color DarkYellow;
    static const sf::Color DarkGreen;
    static const sf::Color DarkBlue;


private:
    static std::unordered_map<std::string, sf::Color> colorMap;
};

#endif // COLOR_H
