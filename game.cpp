#include "game.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
Game::Game() : m_window("Znake",sf::Vector2u(600,600)), player(world.get_block_size()), world(sf::Vector2u(600,600)){

};
void Game::update() {
    float timestep=1.f/player.get_speed();
    if(m_elapsed >= timestep){
        player.tick();
        world.update(player);
        m_elapsed-=timestep;
        if(player.has_lost()){
            player.reset();
        }
    }
}
void Game::render() {
	m_window.begin_draw();
    player.render(*m_window.get_render_window());
    world.render(*m_window.get_render_window());
	m_window.end_draw();
}
Window* Game::get_window() {
    return &m_window;
}

void Game::handle_input() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player.get_direction() != Direction::Down){
        player.set_direction(Direction::Up);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && player.get_direction() != Direction::Up){
        player.set_direction(Direction::Down);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player.get_direction() != Direction::Right){
        player.set_direction(Direction::Left);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && player.get_direction() != Direction::Left){
        player.set_direction(Direction::Right);
    }
}

float Game::get_elapsed() const {
    return m_elapsed;
}

void Game::restart_clock() {
    m_elapsed=m_clock.restart().asSeconds();
}