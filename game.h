#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "window.h"
#include "world.h"
#include "snake.h"

class Game {
private:
    Window m_window;
    sf::Clock m_clock;
    float m_elapsed;
	sf::Vector2u m_increment;
    Snake player;
    World world;

public:
    Game();
    ~Game(){};

    void handle_input();
    void update();
    void render();
	Window* get_window();
    float get_elapsed() const;
    void restart_clock();
	bool is_snake_drawn() const; 
};

