#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class TextBox {
public:
    void TextBox_init(int size, sf::Color color, bool sel) {
        textBox.setCharacterSize(size);
        textBox.setFillColor(color);
        isSelected = sel;
        isVisible = false;

        // If selected, display underscore
        if (isSelected)
            textBox.setString("_");
        else
            textBox.setString("");
    }

    void setFont(sf::Font& font) {
        textBox.setFont(font);
    }

    void setPosition(sf::Vector2f pos) {
        textBox.setPosition(pos);
    }

    void setLimit(bool ToF) {
        hasLimit = ToF;
    }

    void setLimit(bool ToF, int lim) {
        hasLimit = ToF;
        limit = lim;
    }

    void setSelected(bool sel) {
        isSelected = sel;

        // If not selected, remove underscore
        if (!sel) {
            std::string t = text.str();
            std::string newT = "";
            for (int i = 0; i < t.length(); i++) {
                newT += t[i];
            }
            textBox.setString(newT);
        } else {
            textBox.setString(text.str() + "_");
        }
    }

    std::string getText() {
        return text.str();
    }

    void drawTo(sf::RenderWindow& window) {
        if (isVisible) {
            window.draw(textBox);
            std::cout << 111111;
        }
    }

    void typedOn(sf::Event input) {
        if (isSelected) {
            int charTyped = input.text.unicode;

            // Only allow normal inputs
            if (charTyped < 128) {
                if (hasLimit) {
                    // If there's a limit, don't go over it
                    if (text.str().length() <= limit) {
                        inputLogic(charTyped);
                    }
                    // But allow for char deletions
                    else if (text.str().length() > limit && charTyped == DELETE_KEY) {
                        deleteLastChar();
                    }
                }
                // If no limit, just run the function
                else {
                    inputLogic(charTyped);
                }
            }
        }
    }

    void setVisible(bool visible) {
        isVisible = visible;
    }

    bool isEnterPressed() const {
        return enterPressed;
    }

    void resetEnterPressed() {
        enterPressed = false;
    }

private:
    sf::Text textBox;
    std::ostringstream text;
    bool isSelected = false;
    bool hasLimit = false;
    bool isVisible = true;
    bool enterPressed = false;
    int limit = 0;

    // Delete the last character of the text
    void deleteLastChar() {
        std::string t = text.str();
        std::string newT = "";
        for (int i = 0; i < t.length() - 1; i++) {
            newT += t[i];
        }
        text.str("");
        text << newT;

        textBox.setString(text.str() + "_");
    }

    // Get user input
    void inputLogic(int charTyped) {
        // If the key pressed isn't delete, or the two arrow keys, then append the text with the char
        if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY) {
            text << static_cast<char>(charTyped);
        }
        // If the key is delete, then delete the char
        else if (charTyped == DELETE_KEY) {
            if (text.str().length() > 0) {
                deleteLastChar();
            }
        }
        // If the key is enter, set enterPressed to true
        else if (charTyped == ENTER_KEY) {
            enterPressed = true;
        }
        // Set the textbox text
        textBox.setString(text.str() + "_");
    }
};

// Define keys


#endif // TEXTBOX_HPP
