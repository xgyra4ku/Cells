#pragma once
#include <map>
#include <unordered_map>
#include <SFML/Graphics.hpp>
//               id                  клетка                                возраст  вирус           тип   насщ                     нап1   нап2           координаты     
extern std::map<int, std::pair<sf::CircleShape, std::pair<std::pair<std::pair<int, bool>, std::pair<int, int>>, std::pair<std::pair<bool, bool>, std::pair<float, float>>>>> cells;
extern std::map<int, std::pair<sf::CircleShape, std::pair<float, float>>> eats;

