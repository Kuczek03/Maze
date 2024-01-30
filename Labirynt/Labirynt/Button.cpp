#include "Button.h"

Button::Button(float x, float y, float width, float height, const std::string& text, const sf::Font& font, sf::Color bttnClr, sf::Color txtClr) 
	: position(x, y), size(width, height), buttonColor(bttnClr), buttonText(text, font), textColor(txtClr)
{
	buttonShape.setPosition(position);
	buttonShape.setSize(size);
	buttonShape.setFillColor(buttonColor);

	buttonShape.setOutlineColor(sf::Color::Cyan);
	buttonShape.setOutlineThickness(1.f); 

	buttonText.setCharacterSize(24);
	buttonText.setFillColor(textColor);
	buttonText.setOutlineColor(sf::Color::Black);
	buttonText.setOutlineThickness(0.5f);

	sf::FloatRect textBounds = buttonText.getLocalBounds();
	buttonText.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
	buttonText.setPosition(position.x + size.x / 2.f, position.y + size.y / 2.f);
}

bool Button::isMouseOver(const sf::RenderWindow& window) const
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	return buttonShape.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

/*void Button::handleButtonClick() const
{
	std::cout << "Button Clicked!" << std::endl;
}*/


void Button::draw(sf::RenderWindow& window) const
{
	window.draw(buttonShape);
	window.draw(buttonText);
}


