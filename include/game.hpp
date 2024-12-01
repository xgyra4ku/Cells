#pragma onse
#include <map>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <random>
#include <vector>
#include <list>
#include <string>

const int WIDTH = 800;
const int HEIGHT = 1280;


class Game {
    const int inputSize = 8; // Количество входных нейронов
    const int hiddenSize = 20; // Количество скрытых нейронов
    const int outputSize = 4; // Количество выходных нейронов
    const int eatMAX = 200; // максимально еды
    const int timesMAX = 60;// время одго года в кадрах 
    const double mutationRate = 0.01;// шанс мутации
    const int fps = 120; //фпс

    sf::RenderWindow window; // окно

    // Создаем начальный вид
    sf::View view;
    // sf::Font font_w; // шрифт 1
    // sf::Font font_d; // шрифт 2
    // NeuralNetwork nn; // класс нейроннойсети
    // Коэффициент масштабирования
    float zoomFactor = 1.0f;
    float moveSpeed = 5.0f;
    int SCENE = 1; // сцена
    int times = 0;// время
    int speed = 1; // в будусщем скорость действий
    bool stopUPDATE = false;
    int RGBChanges = 1;
    unsigned long long keyCell = 0;

    std::string text; // в будущем текси консли
    sf::Vector2f mousePOS; // позиция мышки
    

   //  std::map<int, std::pair<sf::CircleShape, sf::Vector2f>> eats;//еда
   // struct st_cell//сткуртура  клеток
   //  {
   //      sf::CircleShape shape; // клетка
   //      int age; // возраст
   //      sf::Vector2f position; // позиция
   //      int direction; // направление
   //      float energy; // энергия
   //      sf::Vector3i RGB; // цвет клетки
   //      std::vector<std::vector<double>> weights1; // веса нейронной сети 1
   //      std::vector<std::vector<double>> weights2; // веса нейронной сети 2
    //};
    typedef std::vector<std::vector<int>> weights;//ген
    struct struct_cell
    {
        mutable sf::RectangleShape shape;
        std::vector<int> weights1;//ген
        mutable int type; //тип
        mutable int programCounter = 0; //программа
        int see = 0;
        int parent = -1;
        int energyT[4] = {0,0,0,0};
    };
    //std::map<unsigned long long, struct_cell> cells;//клетки
    std::vector<struct_cell> cells;//клетки
    std::vector<struct_cell> newCells;

    void events();//Эвенты
    void console(); //в будущем консоль
    static double generateCell(double x, double y, double scale, int octaves, double persistence, unsigned int seed);
    void createCell(unsigned int seed);
    void createCell();
    void interpret(const struct_cell& Cell);

    void createCellParent(int type, sf::Vector2f pos, const std::vector<int> &weigs, int programCounter);

    static void updateProgramCounter(const struct_cell &Cell, int count);
    static int updateProgramCounterReturn(const struct_cell &Cell, int count);

public:
    Game();//конструктор
    ~Game();//диструктор

    void run();// начальная функция
};