#include "game.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
Game::Game(const Window &window){
};
void Game::update() {
    m_window.update();
}
void Game::render() {
	m_window.begin_draw();
	//
	m_window.end_draw();
}
Window* Game::get_window() {
    return &m_window;
}

void Game::handle_input() {}

sf::Time Game::get_elapsed() const {
    return m_elapsed;
}

void Game::restart_clock() {
    m_elapsed=m_clock.restart();
}
