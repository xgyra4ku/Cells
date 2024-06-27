#pragma onse
#include "glogal.hpp"

#include "Neurone.hpp"

const int WIDTH = 1280;
const int HEIGHT = 800;


class Game {
private:
    const int inputSize = 5; // Количество входных нейронов
    const int hiddenSize = 10; // Количество скрытых нейронов
    const int outputSize = 4; // Количество выходных нейронов
    const int eatMAX = 200; // максимально еды
    const int timesMAX = 60;// время одго года в кадрах 
    const double mutationRate = 0.01;// шанс мутации
    const int fps = 120; //фпс

    sf::RenderWindow window; // окно
    sf::Font font_w; // шрифт 1
    sf::Font font_d; // шрифт 2
    NeuralNetwork nn; // класс нейроннойсети

    int SCENE = 1; // сцена
    int times = 0;// время 
    int ages = 20; // среднее продолжительность жизни
    int speed = 1; // в будусщем скорость действий
    bool new_cell = false; //появления новой клетки

    std::string text; // в будущем текси консли
    sf::Vector2f mousePOS; // позиция мышки
    

    std::map<int, std::pair<sf::CircleShape, sf::Vector2f>> eats;//еда
   struct st_cell//сткуртура  клеток
    {
        sf::CircleShape shape; // клетка 
        int age; // возраст
        sf::Vector2f position; // позиция
        int direction; // направление
        float energy; // энергия
        sf::Vector3 RGB; // цвет клетки
        std::vector<std::vector<double>> weights1; // веса нейронной сети 1
        std::vector<std::vector<double>> weights2; // веса нейронной сети 2
    };

    std::map<int, st_cell> cells;//клетки

    void createCell(bool mutation, st_cell &cell);//создание клетки
    void createCellNoIntelligence();//создание клетки с помошью команды 
    bool random_bool(float percentage);// рандомный 0/1
    void EatUpdate(); //добавление еды
    bool isWithinTolerance(int number1, int number2, int tolerance);//провекка в радиусе
    double collision_cell(float x, float y, int type, int radius);//проверка в круглом радиусе клетки
    void life();// жизни
    void menu();// меню
    void update();// обновление
    void moveCell(st_cell& cell);//перемещении клетки
    void events();//Эвенты
    void console(); //в будущем консоль
public:
    Game();//конструктор
    ~Game();//диструктор
    void run();// начальная функция
};