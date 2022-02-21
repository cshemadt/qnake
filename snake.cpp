#include "snake.h"
#include <SFML/System/Vector2.hpp>
#include <iostream>

Snake::Snake(int size) : m_size(size){
	m_body_rect.setSize(sf::Vector2f(m_size-1,m_size-1));
	reset();
}
Snake::~Snake(){}
void Snake::reset(){
	m_body.clear();
	
	m_body.push_back(SnakeSegment(5,7));
	m_body.push_back(SnakeSegment(5,6));
	m_body.push_back(SnakeSegment(5,5));
	
	set_direction(Direction::None);

	m_speed=15;
	m_lives=3;
	m_score=0;
	m_lost = false;
}

//Helpers methods implementation
void Snake::set_direction(Direction direction) { m_curr_direction = direction; }
int Snake::get_speed() const { return m_speed; }
int Snake::get_score() const { return m_score; }
int Snake::get_lives() const { return m_lives; }
bool Snake::has_lost() const { return m_lost; }
sf::Vector2i Snake::get_position() const {
	return (m_body.empty() ? sf::Vector2i(1,1) : m_body.front().position);
}
void Snake::lose() { m_lost = true; }
void Snake::toggle_lost() {m_lost = !m_lost; }
void Snake::increase_score() { m_score += 1; }
Direction Snake::get_direction() const { return m_curr_direction; }

