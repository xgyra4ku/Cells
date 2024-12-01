#include "../include/game.hpp"
#include "../include/glogal.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include "../include/PerlinNoise.hpp"

// Конструктор
Game::Game() : window(sf::VideoMode(1280, 800), "SFML Window") {
    view = window.getDefaultView();
}

// Деструктор
Game::~Game() = default;

// Главная функция
void Game::run() {
    sf::Vector2i mousePos = sf::Mouse::getPosition();
    //createCell(123344);
    window.setFramerateLimit(fps);
    std::random_device rd;  // Источник случайности
    std::mt19937 gen(rd()); // Генератор случайных чисел
    std::uniform_int_distribution<> distrib(0,  1280); // Диапазон значений
    for (int i = 0; i < 500; i++) {
        mousePOS = {static_cast<float>(distrib(gen)), static_cast<float>(distrib(gen))};
        createCell();
    }

    sf::VertexArray visibleCells; // Для хранения видимых клеток
    while (window.isOpen()) {
        events();

        // Управление перемещением вида
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle) && sf::Mouse::getPosition().x > mousePos.x) {
            view.move(-moveSpeed, 0); // Влево
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle) && sf::Mouse::getPosition().x < mousePos.x) {
            view.move(moveSpeed, 0); // Вправо
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle) && sf::Mouse::getPosition().y > mousePos.y) {
            view.move(0, -moveSpeed); // Вверх
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle) && sf::Mouse::getPosition().y < mousePos.y) {
            view.move(0, moveSpeed); // Вниз
        }
        mousePos = sf::Mouse::getPosition();
        window.setView(view);

        window.clear(sf::Color::White);

        // Получение границ видимой области
        sf::FloatRect visibleArea(
            view.getCenter().x - view.getSize().x / 2,
            view.getCenter().y - view.getSize().y / 2,
            view.getSize().x,
            view.getSize().y
        );

        // Создание массива видимых клеток
        visibleCells.clear();
        visibleCells.setPrimitiveType(sf::Quads);
        //const unsigned long size = cells.size();
        //for (int i = 0; i < size; ++i) {
        for (auto cell : cells) {
            //struct_cell cell = cells[i];
            interpret(cell);
            // Проверка видимости клетки
            if (visibleArea.intersects(cell.shape.getGlobalBounds())) {
                auto bounds = cell.shape.getGlobalBounds();
                sf::Color color = cell.shape.getFillColor();

                visibleCells.append(sf::Vertex(sf::Vector2f(bounds.left, bounds.top), color)); // Верхний левый
                visibleCells.append(sf::Vertex(sf::Vector2f(bounds.left + bounds.width, bounds.top), color)); // Верхний правый
                visibleCells.append(sf::Vertex(sf::Vector2f(bounds.left + bounds.width, bounds.top + bounds.height), color)); // Нижний правый
                visibleCells.append(sf::Vertex(sf::Vector2f(bounds.left, bounds.top + bounds.height), color)); // Нижний левый
            }
        }

        // Отрисовка видимых клеток
        window.draw(visibleCells);
        window.display();
    }
}

void Game::interpret(const struct_cell& Cell) {
    //интерпритация клеток
    if (Cell.type == 1) {
        //std::cout << 423 << std::endl;
        int counter = Cell.programCounter;
        //std::cout << 153 << std::endl;
        const int command = Cell.weights1[counter];
        //std::cout << 413 << std::endl;
        //std::cout << "Command: " << command << std::endl;
        //std::cout << "Parent: " << Cell.parent << std::endl;



        //std::cout << "Weigs size: " << Cell.weights1.size() << std::endl;
        //for (size_t i = 0; i < Cell.weights1.size(); ++i) {
        //    std::cout << "Weigs[" << i << "] = " << Cell.weights1[i] << std::endl;
        //}


        if (command == 26) {
            counter = updateProgramCounterReturn(Cell, 1);
            const int weight = Cell.weights1[counter];
            int viewCell = weight % 8;
            // есть ли клетка там куда хочет переместиться
            bool isCell = false;
            for (const auto& cell : cells) {
                sf::Vector2f pos = cell.shape.getPosition();
                if (viewCell == 0) {
                    if (pos.x+8 == Cell.shape.getPosition().x && pos.y-8 == Cell.shape.getPosition().y) {
                        counter = updateProgramCounterReturn(Cell, 1);
                        isCell = true;
                        break;
                    } isCell = false;
                }if (viewCell == 1) {
                    if (pos.x+8 == Cell.shape.getPosition().x && pos.y == Cell.shape.getPosition().y) {
                        counter = updateProgramCounterReturn(Cell, 2);
                        isCell = true;
                        break;
                    }isCell = false;
                }if (viewCell == 2) {
                    if (pos.x+8 == Cell.shape.getPosition().x && pos.y+8 == Cell.shape.getPosition().y) {
                        counter = updateProgramCounterReturn(Cell, 3);
                        isCell = true;
                        break;
                    }isCell = false;
                }if (viewCell == 3) {
                    if (pos.x == Cell.shape.getPosition().x && pos.y+8 == Cell.shape.getPosition().y) {
                        counter = updateProgramCounterReturn(Cell, 4);
                        isCell = true;
                        break;
                    }isCell = false;
                }if (viewCell == 4) {
                    if (pos.x-8 == Cell.shape.getPosition().x && pos.y+8 == Cell.shape.getPosition().y) {
                        counter = updateProgramCounterReturn(Cell, 5);
                        isCell = true;
                        break;;
                    }isCell = false;
                }if (viewCell == 5) {
                    if (pos.x-8 == Cell.shape.getPosition().x && pos.y == Cell.shape.getPosition().y) {
                        counter = updateProgramCounterReturn(Cell, 6);
                        isCell = true;
                        break;
                    }
                    isCell = false;
                }if (viewCell == 6) {
                    if (pos.x-8 == Cell.shape.getPosition().x && pos.y-8 == Cell.shape.getPosition().y) {
                        counter = updateProgramCounterReturn(Cell, 7);
                        isCell = true;
                        break;
                    }
                    isCell = false;

                }if (viewCell == 7) {
                    if (pos.x == Cell.shape.getPosition().x && pos.y-8 == Cell.shape.getPosition().y) {
                        counter = updateProgramCounterReturn(Cell, 8);
                        isCell = true;
                        break;
                    }
                    isCell = false;
                }

            }
            if (!isCell) {
                counter = updateProgramCounterReturn(Cell, 9);
                if (viewCell == 0) {
                    Cell.shape.setPosition(Cell.shape.getPosition().x + 8, Cell.shape.getPosition().y - 8);
                }if (viewCell == 1) {
                    Cell.shape.setPosition(Cell.shape.getPosition().x + 8, Cell.shape.getPosition().y);
                }if (viewCell == 2) {
                    Cell.shape.setPosition(Cell.shape.getPosition().x + 8, Cell.shape.getPosition().y + 8);
                }if (viewCell == 3) {
                    Cell.shape.setPosition(Cell.shape.getPosition().x, Cell.shape.getPosition().y + 8);
                }if (viewCell == 4) {
                    Cell.shape.setPosition(Cell.shape.getPosition().x - 8, Cell.shape.getPosition().y + 8);
                }if (viewCell == 5) {
                    Cell.shape.setPosition(Cell.shape.getPosition().x - 8, Cell.shape.getPosition().y);
                }if (viewCell == 6) {
                    Cell.shape.setPosition(Cell.shape.getPosition().x - 8, Cell.shape.getPosition().y - 8);
                }if (viewCell == 7) {
                    Cell.shape.setPosition(Cell.shape.getPosition().x, Cell.shape.getPosition().y - 8);
                }
            }

        }else if (command == 25) { //фотоси
            counter = updateProgramCounterReturn(Cell, 1);
            Cell.type = 0;
            Cell.shape.setFillColor(sf::Color(100,100,100));
            //createCellParent(1, sf::Vector2f{Cell.shape.getPosition().x+8, Cell.shape.getPosition().y}, Cell.weights1, 2);
            //std::cout << 334 << std::endl;
            //int w = Cell.weights1[counter];
            // int quantity = 1 + (w / 63) * (3 - 1);
            // for (int i = 0; i < quantity; i++) {
            //     counter = updateProgramCounterReturn(Cell, 1);
            //     w = Cell.weights1[counter];
            //     int type = 1 + (w / 63);
            //     createCell(type, sf::Vector2f{Cell.shape.getPosition().x+8, Cell.shape.getPosition().y}, Cell.weights1, 4);
            // }
            //counter = updateProgramCounterReturn(Cell, 1);
            // w = Cell.weights1[counter];
            //int type = 1 ;//
            //createCellParent(type, sf::Vector2f{Cell.shape.getPosition().x+8, Cell.shape.getPosition().y}, Cell.weights1, 4);

        } else {
            counter = updateProgramCounterReturn(Cell, counter);
            // std::cout << counter << std::endl;
        }
    }

}
void Game::createCellParent(const int type, const sf::Vector2f pos, const std::vector<int>& weigs, const int programCounter) {

    // Создаем клетку
    sf::RectangleShape rect(sf::Vector2f(8, 8)); // Размер клетки 1x1
    rect.setPosition(pos); // Устанавливаем позицию клетки
    rect.setFillColor(sf::Color::Green); // Задаем цвет клетки
    std::vector<int> weigs1;
    for (int i = 0; i < 64; i++) {
        if (i < weigs.size()) {
            int w = weigs[i];
           // std::cout << w << " " << i << "     ";
            weigs1.push_back(w);
        } else {
            // Если элемент отсутствует, добавляем значение по умолчанию
            //std::cout << "Default value for index " << i << std::endl;
            weigs1.push_back(0);
        }
    }
    //std::cout << std::endl;
    //std::cout << std::endl;
    //std::cout << std::endl;

    cells.push_back({rect, weigs1, 1,0,0,4 });
    //std::cout << 3 << std::endl;

}

void Game::updateProgramCounter(const struct_cell &Cell, const int count) {
    int counter = Cell.programCounter + count;
    if (counter > 63) counter = 0;
    Cell.programCounter = counter;
}

int Game::updateProgramCounterReturn(const struct_cell &Cell, const int count) {
    int counter = Cell.programCounter + count;
    if (counter > 63) counter = 0;
    Cell.programCounter = counter;
    return counter;
}



// Обработка событий
void Game::events() {
    sf::Event event{};
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseWheelScrolled:
                view.zoom(event.mouseWheelScroll.delta > 0 ? 0.9f : 1.1f); // Масштабирование
                break;

            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    mousePOS = {static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)};
                    createCell();
                }
                break;

            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Space) {
                    stopUPDATE = !stopUPDATE;
                }
                break;

            default:
                break;
        }
    }
}

// Генерация перлин-шумов
double Game::generateCell(double x, double y, double scale, int octaves, double persistence, unsigned int seed) {
    PerlinNoise perlin(seed);
    return perlin.octave2D_01(x * scale, y * scale, octaves, persistence);
}

// Создание клеток
void Game::createCell(unsigned int seed) {
    constexpr double persistence = 0.01;
    constexpr int octaves = 8;
    constexpr double scale = 0.2;

    std::vector<std::vector<double>> noiseValues(WIDTH + 2, std::vector<double>(HEIGHT + 2, 0.0));

    for (int y = -1; y <= WIDTH; ++y) {
        for (int x = -1; x <= HEIGHT; ++x) {
            noiseValues[y + 1][x + 1] = generateCell(x, y, scale, octaves, persistence, seed);
        }
    }

    for (int y = 0; y < WIDTH; ++y) {
        for (int x = 0; x < HEIGHT; ++x) {
            if (noiseValues[y][x] > 0.5) {
                sf::RectangleShape rect(sf::Vector2f(1, 1));
                rect.setPosition(static_cast<float>(x), static_cast<float>(y));
                rect.setFillColor(sf::Color::Green);
                cells.push_back({rect});
            }
        }
    }
}


void Game::createCell() {
    // Создаем генератор случайных чисел
    std::random_device rd;  // Источник случайности
    std::mt19937 gen(rd()); // Генератор случайных чисел
    std::uniform_int_distribution<> distrib(0, 63); // Диапазон значений

    // Создаем клетку
    sf::RectangleShape rect(sf::Vector2f(8, 8)); // Размер клетки 1x1
    rect.setPosition(mousePOS); // Устанавливаем позицию клетки
    rect.setFillColor(sf::Color::Green); // Задаем цвет клетки

    // Инициализируем матрицу весов
    std::vector<int> localWeights(64, 0);

    for (int i = 0; i < 64; ++i) {
            localWeights[i] = distrib(gen); // Заполняем случайными значениями
            //std::cout << localWeights[i] << " "; // Отладочный вывод

    }
    //std::cout << std::endl;

    // Добавляем новую клетку в список
    cells.push_back({rect, localWeights, 1, 0});
}
