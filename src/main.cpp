//клетки
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <map>
#include <random>
#include <vector>
#include <chrono>
#include <list>

using namespace sf;
    
const int WIDTH = 1280;
const int HEIGHT = 800;
int times = 0;
int ages = 20;
int eat_maks = 200;
//        id                  клетка                                возраст  вирус           тип   насщ                     нап1   нап2           координаты     
std::map<int, std::pair<sf::CircleShape, std::pair<std::pair<std::pair<int, bool>, std::pair<int, int>>, std::pair<std::pair<bool, bool>, std::pair<float, float>>>>> cells;
std::map<int, std::pair<sf::CircleShape, std::pair<float, float>>> eats;

void createCell(float pos_x, float pos_y, int type) {
    bool b1 = rand() % 2;
    bool b2 = rand() % 2;
    sf::CircleShape circle(static_cast<float>(5));
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(static_cast<float>(pos_x), static_cast<float>(pos_y));
    cells[10 + rand() % (100000 - 10 + 1)] = std::make_pair(circle, std::make_pair(std::make_pair(std::make_pair(1, false), std::make_pair(type, 50)), std::make_pair(std::make_pair(b1, b2), std::make_pair(pos_x, pos_y))));
}
bool random_bool(int percentage) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    
    std::uniform_int_distribution<int> distribution(0, 999);
    
    int random_value = distribution(generator);
    return random_value < percentage;
}

bool generateRandomBool() {
    return rand() % 2;
}

void eat_pulse() {
    if (eats.size() < eat_maks) {
        int pos_x = 0 + rand() % WIDTH;
        int pos_y = 0 + rand() % HEIGHT;
        sf::CircleShape circle(static_cast<float>(2));
        circle.setFillColor(sf::Color(208, 24, 225));
        circle.setPosition(static_cast<float>(pos_x), static_cast<float>(pos_y));
        eats[10 + rand() % (100000 - 10 + 1)] = std::make_pair(circle, std::make_pair(static_cast<float>(pos_x), static_cast<float>(pos_y)));
    }

}
bool isWithinTolerance(int number1, int number2, int tolerance) {
    return std::abs(number1 - number2) <= tolerance;
}

int collision_cell(float x, float y, int type, int radius) {
    for (auto& cell_e : cells)
    {
        //std::pair<sf::CircleShape, std::pair<std::pair<std::pair<int, bool>, std::pair<int, int>, std::pair<std::pair<bool, bool>, std::pair<float, float>>>>
        auto& cell_1_e = cell_e.second;
        //std::pair<std::pair<std::pair<int, bool>, std::pair<int, int>, std::pair<std::pair<bool, bool>, std::pair<float, float>>>
        auto& cell_2_e = cell_1_e.second;
        //std::pair<int, bool>, std::pair<int, int>
        auto& cell_3_e = cell_2_e.first;
        //std::pair<std::pair<bool, bool>, std::pair<float, float>
        auto& cell_4_e = cell_2_e.second;
        //std::pair<int, bool>
        auto& cell_5_e = cell_3_e.first;
        //std::pair<int, int>
        auto& cell_6_e = cell_3_e.second;
        //std::pair<bool, bool>
        auto& cell_7_e = cell_4_e.first;
        //std::pair<float, float>
        auto& cell_8_e = cell_4_e.second;
        if (cell_6_e.first == type && isWithinTolerance(x, cell_8_e.first, radius) && isWithinTolerance(y, cell_8_e.second, radius))
            return cell_e.first;
    }
    return -1; 
}

void life(RenderWindow& window) {
    std::list<int> dead_eats;
    std::list<int> dead_cells;
    int el = 0;
    times++;
    for(auto& cell : cells) {   //std::map<int, std::pair<sf::CircleShape, std::pair<std::pair<std::pair<int, bool>, std::pair<int, int>, std::pair<std::pair<bool, bool>, std::pair<float, float>>>> cells;

        //std::pair<sf::CircleShape, std::pair<std::pair<std::pair<int, bool>, std::pair<int, int>, std::pair<std::pair<bool, bool>, std::pair<float, float>>>>
        auto& cell_1 = cell.second;
        //std::pair<std::pair<std::pair<int, bool>, std::pair<int, int>, std::pair<std::pair<bool, bool>, std::pair<float, float>>>
        auto& cell_2 = cell_1.second;
        //std::pair<int, bool>, std::pair<int, int>
        auto& cell_3 = cell_2.first;
        //std::pair<std::pair<bool, bool>, std::pair<float, float>
        auto& cell_4 = cell_2.second;
        //std::pair<int, bool>
        auto& cell_5 = cell_3.first;//возраст заражон да/нет
        //std::pair<int, int>
        auto& cell_6 = cell_3.second;//тип насщения
        //std::pair<bool, bool>
        auto& cell_7 = cell_4.first;//направление
        //std::pair<float, float>
        auto& cell_8 = cell_4.second;//кординаты
        
        if (cell_6.first != 2){ // 1 обычная клетка 2 мертвая 3 заражена вирусом 4 антиген
            if (cell_6.first == 1)
                cell_1.first.setFillColor(sf::Color::Green);
            else if (cell_6.first == 3)
                cell_1.first.setFillColor(sf::Color::Red);
            else if (cell_6.first == 4)
                cell_1.first.setFillColor(sf::Color::Blue);
            
            if (random_bool(10) && cell_6.second >= 100) {
                int ran_nd = 1 + rand() % 3;
                if (ran_nd == 3 && random_bool(6))
                    createCell(cell_8.first -20, cell_8.second + 20, 3);
                else if (ran_nd == 2 && random_bool(50))
                    createCell(cell_8.first-10, cell_8.second-10, 4);
                else
                    createCell(cell_8.first-10, cell_8.second-10, 1); 
                cell_6.second = 50;
            }

            if (cell_6.second < 0)
                cell_6.first = 2;            
            if (cell_5.second && random_bool (15))
                cell_6.first = 2;
            else if (random_bool(1) && random_bool(1))
                cell_6.first = 2;
            
            if (cell_6.first == 1 || cell_6.first == 4) {
                for (auto& eat : eats) {
                    if (isWithinTolerance(cell_8.first, eat.second.second.first, 20) && isWithinTolerance(cell_8.second, eat.second.second.second, 20)) {
                        cell_6.second += 30;
                        dead_eats.push_back(eat.first);
                        break;
                    }
                }
            } else if (cell_6.first == 3) {
                int cell_dead_eats = collision_cell(cell_8.first, cell_8.second, 2, 20);
                if (cell_dead_eats != -1) {
                    dead_cells.push_back(cell_dead_eats);
                    cell_6.second -= 10;
                }
            }
            
            if (cell_6.first == 4) {
                int antibodies = collision_cell(cell_8.first, cell_8.second, 3, 20);
                if (antibodies != -1){
                    dead_cells.push_back(antibodies);
                    dead_cells.push_back(cell.first);
                }
            } else if (cell_6.first == 1) {
                int virus = collision_cell(cell_8.first, cell_8.second, 3, 20);
                if (virus != -1) {
                    cell_6.first = 3;
                }   
            }
            
            // движение 
            if (cell_7.first) {
                cell_8.first += 1;
            } else {
                cell_8.first -= 1;
            }
            if (cell_7.second) {
                cell_8.second += 1;
            } else {
                cell_8.second -= 1;
            }

            if (cell_8.first < 0) {
                cell_7.first = true;
            } else if (cell_8.first > WIDTH - 10) {
                cell_7.first = false;
            }
            if (cell_8.second < 0) {
                cell_7.second = true;
            } else if (cell_8.second > HEIGHT - 10) {
                cell_7.second = false;
            }
            if (random_bool(1)) {
                if (random_bool(50)) {
                    cell_7.first = !cell_7.first;
                } else {
                    cell_7.second = !cell_7.second;
                }
            }

            cell_1.first.setPosition(cell_8.first, cell_8.second);

            ages = (cell_5.first + ages) / 2;
        } else {
            cell_1.first.setFillColor(sf::Color::Black);
        }
    }

    if (times >= 50) {
        int el = 0;
        for (auto& cell : cells) {
            
            //std::pair<sf::CircleShape, std::pair<std::pair<std::pair<int, bool>, std::pair<int, int>, std::pair<std::pair<bool, bool>, std::pair<float, float>>>>
            auto& cell_1 = cell.second;
            //std::pair<std::pair<std::pair<int, bool>, std::pair<int, int>, std::pair<std::pair<bool, bool>, std::pair<float, float>>>
            auto& cell_2 = cell_1.second;
            //std::pair<int, bool>, std::pair<int, int>
            auto& cell_3 = cell_2.first;
            //std::pair<std::pair<bool, bool>, std::pair<float, float>
            auto& cell_4 = cell_2.second;
            //std::pair<int, bool>
            auto& cell_5 = cell_3.first;
            //std::pair<int, int>
            auto& cell_6 = cell_3.second;
            //std::pair<bool, bool>
            auto& cell_7 = cell_4.first;
            //std::pair<float, float>
            auto& cell_8 = cell_4.second;

            cell_5.first++;

            if (cell_6.first != 2) {
                el++;
                cell_6.second -= 5;
            } else if (cell_5.first > 150) {
                dead_cells.push_back(cell.first);
            }
        }
        std::cout << "Elements: " <<el << std::endl;
        std::cout << "Age: " << ages << std::endl;
        times = 0; 
    }

    for (auto& eat : dead_eats) {
        eats.erase(eat);
    }
    for (auto& dead : dead_cells) {
        cells.erase(dead);
    }
    dead_eats.clear();
    dead_cells.clear();
}

int main() {
    int pos_x = 0;
    int pos_y = 0;
    bool new_cell = false;
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "Cellular Life");
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {    
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                new_cell = false;
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && !new_cell) {
                pos_x = event.mouseButton.x;
                pos_y = event.mouseButton.y;
                new_cell = true;
            }
        }
        life(window);
        eat_pulse();

        if (new_cell) {
            createCell(pos_x, pos_y, 1);
            new_cell = false;
        }
        window.clear(sf::Color::White);

        window.setFramerateLimit(120);

        
        for (const auto& eat : eats) {
            window.draw(eat.second.first);
        }
        for (const auto& cell : cells) {
            window.draw(cell.second.first);
        }

        window.display();
    }
    return 0;
}
