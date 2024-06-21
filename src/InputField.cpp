#include "../include/InputField.hpp"

void InputField::init(float x, float y, float width, float height, sf::Font font) {
    box.setPosition(x, y);
    box.setSize(sf::Vector2f(width, height));
    box.setFillColor(sf::Color::White);
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(1);

    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(height - 10); // уменьшаем размер шрифта
    text.setPosition(x + 5, y + 5);

    isActive = false;
}

void InputField::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (box.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
            isActive = true;
        } else {
            isActive = false;
        }
    }

    if (event.type == sf::Event::TextEntered && isActive) {
        if (event.text.unicode == 8 && !inputString.empty()) { // Backspace
            inputString.pop_back();
        } else if (event.text.unicode >= 32 && event.text.unicode <= 126) { // Displayable characters
            inputString += static_cast<char>(event.text.unicode);
        }
        updateText();
    }
}

void InputField::draw(sf::RenderWindow& window) {
    window.draw(box);
    window.draw(text);
}

std::string InputField::getText() const {
    return inputString;
}

void InputField::updateText() {
    text.setString(inputString);
}
