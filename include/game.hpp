#include "glogal.hpp"
#include "InputField.hpp"

const int WIDTH = 1280;
const int HEIGHT = 800;


class Game {
std::map<int, std::pair<sf::CircleShape, std::pair<std::pair<std::pair<int, bool>, std::pair<int, int>>, std::pair<std::pair<bool, bool>, std::pair<float, float>>>>> cells;
std::map<int, std::pair<sf::CircleShape, std::pair<float, float>>> eats;
private:
    //variables
    int SCENE = 1;
    bool CONSOLE = false;

    sf::RenderWindow window;
    InputField inputField;
    sf::Font font_w;
    sf::Font font_d;
    bool new_cell = false;
    int pos_x = 0;
    int pos_y = 0;

    int times = 0;
    int ages = 20;
    int eat_maks = 200;

    int fps = 120;

    int speed = 1;

    std::string text;


    //function
    void createCell(float pos_x, float pos_y, int type) ;
    bool random_bool(int percentage);
    bool generateRandomBool();
    void eat_pulse();
    bool isWithinTolerance(int number1, int number2, int tolerance);
    int collision_cell(float x, float y, int type, int radius);
    void life();
    void menu();
    void update();

    void events();
    void update_scene_game();

    void console(); 

    void font_init();

public:
    Game();
    ~Game();

    void run();
};