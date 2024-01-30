#pragma once
#include "asstes.h"
using namespace std;

class Button {
private:
    sf::RectangleShape buttonShape;
    sf::Vector2f position;
    sf::Vector2f size;
    sf::Color buttonColor;
    sf::Color textColor;
    sf::Text buttonText;
public:
    Button(float x, float y, float width, float height, const std::string& text, 
        const sf::Font& font, sf::Color bttnClr, sf::Color txtClr);        

    bool isMouseOver(const sf::RenderWindow& window) const;
    void draw(sf::RenderWindow& window) const;
};
