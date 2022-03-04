#include "snake.h"
#include <SFML/System/Vector2.hpp>
#include <iostream>

Snake::Snake(int size, int grid_x_size, int grid_y_size, int block_size ) : m_size(size), m_grid_x_size(grid_x_size), m_grid_y_size(grid_y_size), m_block_size(block_size){
	m_body_rect.setSize(sf::Vector2f(m_size-1,m_size-1));
	reset();
}
Snake::~Snake(){}

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
Direction Snake::get_direction() {
	if(m_body.size() <= 1){ return Direction::None; }
	SnakeSegment &head = m_body[0];
	SnakeSegment &neck = m_body[1];

	if(head.position.x == neck.position.x) {
		return head.position.y > neck.position.y ? Direction::Down : Direction::Up; 
	} else if(head.position.y == neck.position.y) {
		return head.position.x > neck.position.x ? Direction::Right : Direction::Left;
	}
	return Direction::None;
}

//Move snake to starting point and reset some game parameters
void Snake::reset(){
	m_body.clear();
	m_body.push_back(SnakeSegment(5,6));
	m_body.push_back(SnakeSegment(5,5));
	m_body.push_back(SnakeSegment(5,4));	
	set_direction(Direction::None);

	m_speed=20;
	m_lives=3;
	m_score=0;
	m_lost = false;
}
//Changing(extending) snake's size
void Snake::extend(){
	if(m_body.empty()){ return; }
	SnakeSegment tail_head = m_body.at(m_body.size()-1);

	if(m_body.size() > 1){
		//Second to last segment of snake's body
		SnakeSegment tail_bone = m_body.at(m_body.size()-2);
		
		//Considering the situation when tail's head and bone have the same x axis
		//(i.e snake places vertically)
		if(tail_bone.position.x == tail_head.position.x){
			//If snake 'looks' up
			if(tail_head.position.y > tail_bone.position.y){
				m_body.push_back(SnakeSegment(tail_head.position.x,tail_head.position.y + 1));
			} else {
				m_body.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y - 1));
			}
		}
		//If snake places horizontally
		else if(tail_bone.position.y == tail_head.position.y) {
			if(tail_head.position.x > tail_bone.position.x){
				m_body.push_back(SnakeSegment(tail_head.position.x + 1, tail_head.position.y));
			}  else{
				m_body.push_back(SnakeSegment(tail_head.position.x - 1, tail_head.position.y));
			}
		}
	}
	else{
		if(m_curr_direction == Direction::Up) {
			m_body.push_back(SnakeSegment(tail_head.position.x,tail_head.position.y+1));
		} else if(m_curr_direction == Direction::Down) {
			m_body.push_back(SnakeSegment(tail_head.position.x,tail_head.position.y-1));
		} else if(m_curr_direction == Direction::Left) {
			m_body.push_back(SnakeSegment(tail_head.position.x+1,tail_head.position.y));
		} else if(m_curr_direction == Direction::Right) {
			m_body.push_back(SnakeSegment(tail_head.position.x-1,tail_head.position.y));
		}
	}
}
void Snake::tick() {
	if(m_body.empty() || m_curr_direction == Direction::None){ return; }
	check_collision_with_wall();
	move();
	check_collision();
	
}
void Snake::move() {
	for(int i=m_body.size()-1;i>0;--i){
		m_body.at(i).position = m_body.at(i-1).position;
	}
	if(m_curr_direction == Direction::Left) {
		--m_body.at(0).position.x;
	}
	if(m_curr_direction == Direction::Right) {
		++m_body.at(0).position.x;
	}
	if(m_curr_direction == Direction::Up) {
		--m_body.at(0).position.y;
	}
	if(m_curr_direction == Direction::Down) {
		++m_body.at(0).position.y;
	}
}
void Snake::check_collision() {
	if(m_body.size() < 5) { return; }
	SnakeSegment &snake_head = m_body.front();
	for(auto itr = m_body.begin() + 1; itr!=m_body.end(); ++itr){
		if(itr->position == snake_head.position){
			int segments=m_body.end() - itr+1;
			cut(segments);
			break;
		}
	}
}
void Snake::cut(int segments) {
	for(int i=0;i<segments;++i){
		m_body.pop_back();
	}
	//--m_lives;
	//if(m_lives==0){
		lose();
		return; 
	//}
}

void Snake::render(sf::RenderWindow &window) {
	if(m_body.empty()){ return; }
	auto head = m_body.begin();
	m_body_rect.setFillColor(sf::Color::Yellow);
	m_body_rect.setPosition(head->position.x*m_size,head->position.y*m_size);
	window.draw(m_body_rect);
	m_body_rect.setFillColor(sf::Color::Green);
	for(auto itr=m_body.begin()+1;itr!=m_body.end();++itr){
		m_body_rect.setPosition(itr->position.x*m_size,itr->position.y*m_size);
		window.draw(m_body_rect);
	}
}

void Snake::check_collision_with_wall(){
	if(m_body.at(0).position.x >= m_grid_x_size - 1.5){
		m_body.at(0).position.x = 0.5;
	} else if(m_body.at(0).position.x <= 0){
		m_body.at(0).position.x = m_grid_x_size-1.5;
	}else if(m_body.at(0).position.y >= m_grid_y_size-1.5){
		m_body.at(0).position.y = 1.5;
	} else if(m_body.at(0).position.y <= 0.5){
		m_body.at(0).position.y = m_grid_y_size-1.5;
	}
}
