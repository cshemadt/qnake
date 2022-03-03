#include "world.h"
#include <iostream>
World::World(sf::Vector2u wind_size) : m_window_size(wind_size) {
    m_block_size = 16;
    respawn_apple();
    m_apple.setFillColor(sf::Color::Red);
    m_apple.setRadius(m_block_size/2);

    for (int i = 0; i < 4; ++i) {
        m_bounds[i].setFillColor(sf::Color::White);
        // !!!
        if(i%2!=0) {
            m_bounds[i].setSize(sf::Vector2f(m_window_size.x,m_block_size));
        } else {
            m_bounds[i].setSize(sf::Vector2f(m_block_size,m_window_size.y));
        }
        if(i < 2) {
            m_bounds[i].setPosition(0,0);
        } else {
            m_bounds[i].setOrigin(m_bounds[i].getSize());
            m_bounds[i].setPosition(sf::Vector2f(m_window_size));
        }
    }
}
World::~World(){}
void World::respawn_apple(){
    int max_x=(m_window_size.x / m_block_size)-2;
    int max_y=(m_window_size.y / m_block_size)-2;

    m_item = sf::Vector2i(rand() % max_x+1, rand() % max_y+1);
    m_apple.setPosition(m_item.x*m_block_size,m_item.y*m_block_size);
}
void World::update(Snake &player){
    if(player.get_position() == m_item) {
        player.extend();
        player.increase_score();
        respawn_apple();
    }
    int grid_x_size=m_window_size.x/m_block_size;
    int grid_y_size=m_window_size.y/m_block_size;
    //TODO: make separate function for checking collisions with walls
    if(player.get_position().x >= grid_x_size-1 || player.get_position().x <=0 || player.get_position().y<=0 || player.get_position().y>=grid_y_size-1) {
        player.lose();
    }
}
void World::render(sf::RenderWindow &window){
    for (int i = 0; i < 4; ++i) {
        window.draw(m_bounds[i]);
    }
    window.draw(m_apple);
}
int World::get_block_size() const{
    return m_block_size;
}
