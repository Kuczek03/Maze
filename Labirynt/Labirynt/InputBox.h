#pragma once
#include "asstes.h"
class InputBox 
{
private:
    sf::RenderWindow window;
    sf::Text titleText;
    sf::Text filenameText;

    sf::Text rText;
    sf::Text cText;
    sf::Text wText;
    string userInput1;
    string userInput2;
    string userInput3;

    string userInput;
    int inputStage = 0;
    void handleEvents();
    void handleTextEntered(sf::Uint32 unicode);
    void render();
public:
    InputBox(const string& title, sf::Font& font);
    
    tuple<int, int, double> r3n();
    void handleText3ntered(sf::Uint32 unicode);
    void handle3vents();
    void r3nder();
    string run();


};


