#include "../include/game.hpp"

//конструктор
Game::Game() : window(sf::VideoMode(WIDTH, HEIGHT), "SFML Window") {
    // инициалмзация шрифтов
    if (!font_w.loadFromFile("../font/Sclate.ttf")) {
        std::cerr << "ERROR FONT 1" << std::endl;
        window.close();
    }
    if (!font_d.loadFromFile("../font/SAIBA-45-d.otf")) {
        std::cerr << "ERROR FONT 2" << std::endl;
        window.close();
    }
    std::srand(std::time(NULL)); // инициализация srand
    nn.init(inputSize, hiddenSize, outputSize);//инициализация нейронной сети
}

//диструктор
Game::~Game() {

}

// главная функция
void Game::run() {
    window.setFramerateLimit(fps);
    while (window.isOpen()) {
        events();
        menu();
        window.display();
    }
}  

// в будущем консоль
void Game::console() {
    //...
}

// меню
void Game::menu() {
    if (SCENE == 0) {// сцена меню
        window.clear(sf::Color(0, 0, 0));
    } else if (SCENE == 1) {// сцена програмы
        if (!stopUPDATE) {
            life();
            EatUpdate();
            if (new_cell) {
                createCellNoIntelligence();
                new_cell = false;
            }
            window.clear(sf::Color(255,255,255));
            for (const auto& eat : eats) {
                window.draw(eat.second.first);
            }
            for (const auto& pair : cells) {
                int key = pair.first;
                const st_cell& cell = pair.second;
                window.draw(cell.shape);
            }
        } 
    }
    
}

// эвенты
void Game::events() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {    
            window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                mousePOS = {static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)};
                new_cell = (event.type == sf::Event::MouseButtonReleased);
            }
            
        }
        if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
 
        }  
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Space)
            {
                stopUPDATE = !stopUPDATE;
            }
        }       
    }
}

void Game::createCellNoIntelligence(){
    st_cell new_cell;
    sf::Vector3i RGB = {10 + rand() % 255, 10 + rand() % 255, 10 + rand() % 255};
    sf::CircleShape circle(5.0f);
    circle.setFillColor(sf::Color(RGB.x, RGB.y, RGB.z));
    circle.setPosition(mousePOS.x, mousePOS.y);
    new_cell.shape = circle;
    new_cell.age = 0;
    new_cell.RGB = RGB;
    new_cell.position = mousePOS;
    new_cell.direction = 1 + rand() % 8; 
    new_cell.energy = 50.0f;
    new_cell.weights1 = std::vector<std::vector<double>>(inputSize, std::vector<double>(hiddenSize, 0.0));
    new_cell.weights2 = std::vector<std::vector<double>>(hiddenSize, std::vector<double>(outputSize, 0.0));
    createCell(false, new_cell);
}

// создание клетки
void Game::createCell(bool mutation, st_cell &cell) {
    int rgb = 1 + rand() % 3;
    sf::Vector3i RGB;
    st_cell new_cell;
    sf::CircleShape circle(5.0f);
    switch (rgb)
    {
    case 1:
        if (cell.RGB.x < 255)
            RGB.x = cell.RGB.x + 1;
        else
            RGB.x = 0 + rand() % 255;
    case 2:
        if (cell.RGB.y < 255)
            RGB.y = cell.RGB.y + 1;
        else
            RGB.x = 0 + rand() % 255;
    case 3:
        if (cell.RGB.z < 255)
            RGB.z = cell.RGB.z + 1;
        else
            RGB.z = 0 + rand() % 255; 
    default:
        break;
    }
    // Задание параметров клетки
    circle.setFillColor(sf::Color(RGB.x, RGB.y, RGB.z));
    circle.setPosition(cell.position.x, cell.position.x);
    new_cell.shape = circle;
    new_cell.age = 0;
    new_cell.RGB = RGB;
    new_cell.position = cell.position;
    new_cell.direction = 1 + rand() % 8;
    new_cell.energy = 50.0f;

    // Генерация начальных весов
    new_cell.weights1 = std::vector<std::vector<double>>(inputSize, std::vector<double>(hiddenSize, 0.0));
    new_cell.weights2 = std::vector<std::vector<double>>(hiddenSize, std::vector<double>(outputSize, 0.0));
    

    // Мутация весов
    if (mutation) {
        for (int i = 0; i < cell.weights1.size(); ++i) {
            for (int j = 0; j < cell.weights1[i].size(); ++j) {
                if ((static_cast<double>(rand()) / RAND_MAX) < mutationRate) {
                    new_cell.weights1[i][j] += ((static_cast<double>(rand()) / RAND_MAX) * 0.2 - 0.1);
                }
                else {
                    new_cell.weights1[i][j] = cell.weights1[i][j];
                }
            }
        }
        for (int i = 0; i < cell.weights2.size(); ++i) {
            for (int j = 0; j < cell.weights2[i].size(); ++j) {
                if ((static_cast<double>(rand()) / RAND_MAX) < mutationRate) {
                    new_cell.weights2[i][j] += ((static_cast<double>(rand()) / RAND_MAX) * 0.2 - 0.1);
                }
                else {
                    new_cell.weights2[i][j] = cell.weights2[i][j];
                }
            }
        }
    }
    else {
        for (int i = 0; i < inputSize; ++i) {
            for (int j = 0; j < hiddenSize; ++j) {
                new_cell.weights1[i][j] = (static_cast<double>(rand()) / RAND_MAX) * 2 - 1;
            }
        }
        for (int i = 0; i < hiddenSize; ++i) {
            for (int j = 0; j < outputSize; ++j) {
                new_cell.weights2[i][j] = (static_cast<double>(rand()) / RAND_MAX) * 2 - 1;
            }
        }
    }

    // Добавление новой клетки в коллекцию
    cells[keyCell++] = new_cell;
}

// рандомной 0/1 с указанием процента
bool Game::random_bool(float percentage) {
    int random_value = 0 + rand() % 100;
    return random_value <= percentage;
}

//добавление еды при необходимости
void Game::EatUpdate() {
    if (eats.size() <= eatMAX) {
        int key = -1'000'000'000 + rand() % 1'000'000'000;
        sf::Vector2f pos = {static_cast<float>(0 + rand() % WIDTH), static_cast<float>(0 + rand() % HEIGHT)};
        sf::CircleShape circle(2.0f);
        circle.setFillColor(sf::Color(208, 24, 225));
        circle.setPosition(pos.x, pos.y);
        eats[key] = std::make_pair(circle, pos);
    }
}

// проверака дипазона
bool Game::isWithinTolerance(int number1, int number2, int tolerance) {
    return std::abs(number1 - number2) <= tolerance;
}

// проверка диапазона клетки в кругу
double Game::collision_cell(float x, float y, int type, int radius) {
    int el = 0;
    for (auto& pair : cells)
    {
        int key = pair.first;
        const st_cell& cell = pair.second;
        float X = cell.position.x;
        float Y = cell.position.y;

        if (isWithinTolerance(X, x, radius) && isWithinTolerance(Y, y, radius))
            el++;
    }
    return el; 
}

// главная жинь
void Game::life() {
    std::vector<int> dead_eats;
    times++;
    for(auto& pair : cells) {   
        int key = pair.first;
        st_cell& cell = pair.second;
        sf::Vector2f eat_pos;
        sf::Vector2f cell_left_pos;
        int key_e;

        for (auto& pair_e : cells) {
            key_e = pair_e.first;
            st_cell& cell_e = pair_e.second;
            if (isWithinTolerance(cell.position.x, cell_e.position.x, 20) && isWithinTolerance(cell.position.y, cell_e.position.x, 20)) {
                cell_left_pos = cell_e.position;
                break;
            }
        }
        
        vector<double> normalizedInput = {
            static_cast<double>(cell.age),
            static_cast<double>(cell.energy),
            static_cast<double>(cell.direction),
            static_cast<double>(cell.position.x),
            static_cast<double>(cell.position.y),
            static_cast<double>(eat_pos.x),
            static_cast<double>(eat_pos.y),
            static_cast<double>(cell_left_pos.x),
            static_cast<double>(cell_left_pos.y)
            };

        for (auto& val : normalizedInput) {
            val /= 2000.0; 
        }

        
        //у клетки есть 8 направлений взгляда 
        // output[0] поваачивает в одну сторону на 1 
        // output[1] поварачивает в другую сторону на 1
        // output[2] идти в перед
        // output[3] атака

        
        vector<double> output = nn.feedforward(cell.weights1, cell.weights2, normalizedInput);
        if (output[0] >= 0.5) {
            cell.direction = (cell.direction < 8) ? cell.direction + 1 : 0;
        }
        if (output[1] >= 0.5) {
            cell.direction = (cell.direction > 0) ? cell.direction - 1 : 8;
        }
        if (output[2] >= 0.5) {
            moveCell(cell);
        }
        if (output[3] >= 0.5) {
            for (auto& eat : eats) {
                if (isWithinTolerance(cell.position.x, eat.second.second.x, 20) && isWithinTolerance(cell.position.y, eat.second.second.y, 20)) {
                    cell.energy += 10.0f;
                    dead_eats.push_back(eat.first);
                    eat_pos.x = eat.second.second.x;
                    eat_pos.y = eat.second.second.y;
                    break;
                }
            }
        }
        // Применение обратного распространения ошибки для обновления весов
        // vector<double> targetOutput = { /* цели для обучения */ };
        // vector<vector<double>> gradients = nn.backpropagate(cell.weights1, cell.weights2, normalizedInput, targetOutput);

        // // Обновление весов с использованием градиентов
        // for (int i = 0; i < cell.weights1.size(); ++i) {
        //     for (int j = 0; j < cell.weights1[i].size(); ++j) {
        //         cell.weights1[i][j] -= learningRate * gradients[i][j];
        //     }
        // }
        // for (int i = 0; i < cell.weights2.size(); ++i) {
        //     for (int j = 0; j < cell.weights2[i].size(); ++j) {
        //         cell.weights2[i][j] -= learningRate * gradients[i][j];
        //     }
        // }

                
        if (random_bool(10.0f) && cell.energy >= 100) {
            createCell(true, cell);
            cell.energy = 50;
        }

        cell.shape.setPosition(cell.position.x, cell.position.y);

        ages = (cell.age + ages) / 2;
        cells[key] = cell;
    }

    if (times >= timesMAX) {
        int el = 0;
        for (auto& pair : cells) {
            int key = pair.first;
            st_cell& cell = pair.second;
            cell.age++;
            cell.energy -= 5;
            el++;
        }
        std::cout << "Elements: " << el << std::endl;
        std::cout << "Age: " << ages << std::endl;
        times = 0; 
    }

    for (auto& eat : dead_eats) {
        eats.erase(eat);
    }
    for (auto it = cells.begin(); it != cells.end(); ) {
        int key = it->first;
        st_cell& cell = it->second;
        // Условия для удаления клетки
        if (cell.age > 20 && random_bool(10.0f)) {
            it = cells.erase(it);
            // Можно также добавить дополнительные действия, если необходимо
        } else {
            ++it; // Переход к следующему элементу
        }
    }

    dead_eats.clear();
}


// передвижени клетки
 
void Game::moveCell(st_cell& cell) {
    switch (cell.direction) {
    case 1:
        if (cell.position.y > 0) {
            cell.position.y -= 1;
        }
        break;
    case 2:
        if (cell.position.y > 0) {
            cell.position.y -= 1;
        }
        if (cell.position.x < WIDTH - 10) {
            cell.position.x += 1;
        }
        break;
    case 3:
        if (cell.position.x < WIDTH - 10) {
            cell.position.x += 1;
        }
        break;
    case 4:
        if (cell.position.y < HEIGHT - 10) {
            cell.position.y += 1;
        }
        if (cell.position.x < WIDTH - 10) {
            cell.position.x += 1;
        }
        break;
    case 5:
        if (cell.position.y < HEIGHT - 10) {
            cell.position.y += 1;
        }
        break;
    case 6:
        if (cell.position.x > 0) {
            cell.position.x -= 1;
        }
        if (cell.position.y < HEIGHT - 10) {
            cell.position.y += 1;
        }
        break;
    case 7:
        if (cell.position.x > 0) {
            cell.position.x -= 1;
        }
        break;
    case 8:
        if (cell.position.y > 0) {
            cell.position.y -= 1;
        }
        if (cell.position.x > 0) {
            cell.position.x -= 1;
        }
        break;
    default:
        break;
    }
}