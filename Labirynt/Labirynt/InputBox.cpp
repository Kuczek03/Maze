#include "InputBox.h"

InputBox::InputBox(const string& title, sf::Font& font) {
    sf::Color background(102, 153, 255);
    window.create(sf::VideoMode(400, 200), title);
    
    titleText.setString(title);
    titleText.setCharacterSize(20);
    titleText.setPosition(10, 10);

    filenameText.setCharacterSize(40);
    filenameText.setFont(font);
    filenameText.setPosition(50,60);
    filenameText.setOrigin(filenameText.getLocalBounds().width / 2.f, filenameText.getLocalBounds().height / 2.f);
    filenameText.setFillColor(sf::Color::White);

    rText.setCharacterSize(40);
    rText.setFont(font);
    rText.setPosition(170, 20);
    rText.setFillColor(sf::Color::White);

    cText.setCharacterSize(40);
    cText.setFont(font);
    cText.setPosition(170, 70);
    cText.setFillColor(sf::Color::White);

    wText.setCharacterSize(40);
    wText.setFont(font);
    wText.setPosition(170, 120);
    wText.setFillColor(sf::Color::White);
}
tuple<int, int, double> InputBox::r3n() {
    while (window.isOpen()) {
        handle3vents();
        r3nder();
    }
    try {
        inputStage = 0;
        return make_tuple(std::stoi(userInput1), std::stoi(userInput2), std::stod(userInput3));
    }
    catch (const std::invalid_argument& e) {
        cerr << "Invalid input. Please enter valid numeric values." << std::endl;

        inputStage = 0;
        return make_tuple(10, 10, 0.1);
    }
}
void InputBox::handleText3ntered(sf::Uint32 unicode) {
    

    if ((unicode >= '0' && unicode <= '9') || (unicode == '-' && inputStage == 0 && userInput1.empty())) {
        switch (inputStage) {
        case 0:
            userInput1 += static_cast<char>(unicode);
            rText.setString(userInput1);
            break;
        case 1:
            userInput2 += static_cast<char>(unicode);
            cText.setString(userInput2);
            break;
        case 2:
            userInput3 += static_cast<char>(unicode);
            wText.setString(userInput3);
            break;
        }
    }
    else if (unicode == '.' && inputStage == 2 && userInput3.find('.') == std::string::npos) {
        userInput3 += static_cast<char>(unicode);
        wText.setString(userInput3);
    }
    else if (unicode == ' ') {
        ++inputStage;  
    }
    else if (unicode == ' ' && inputStage > 2) {
        inputStage = 0;
    }

    
}

void InputBox::handle3vents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)) {
            window.close();
        }

        if (event.type == sf::Event::TextEntered) {
            handleText3ntered(event.text.unicode);
        }
    }
}
void InputBox::r3nder() {
    sf::Color background(102, 153, 255);
    window.clear(background);
    window.draw(titleText);
    window.draw(rText);
    window.draw(cText);
    window.draw(wText);
    window.display();
}
string InputBox::run() {
    while (window.isOpen()) {
        handleEvents();
        render();
    }

    return userInput;
}
void InputBox::handleEvents() {
    
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)) {
            window.close();
        }

        if (event.type == sf::Event::TextEntered) {
            handleTextEntered(event.text.unicode);
        }
    }
}

void InputBox::handleTextEntered(sf::Uint32 unicode) {
    if (unicode < 128 && unicode != 8) { 
        userInput += static_cast<char>(unicode);
    }
    else if (unicode == 8 && !userInput.empty()) { 
        userInput.pop_back();
    }

    filenameText.setString(userInput);
}


void InputBox::render() {
    sf::Color background(102, 153, 255);
    window.clear(background);
    window.draw(titleText);
    window.draw(filenameText);
    window.display();
}
