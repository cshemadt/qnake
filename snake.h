#pragma once
#include <SFML/Graphics.hpp>
struct SnakeSegment{
	sf::Vector2i position;
	SnakeSegment(int x, int y) : position(x,y){}; 
};
enum Direction{ None, Up, Down, Left, Right};
class Snake{
	using snake_container = std::vector<SnakeSegment>;	
public:
	Snake(int, int, int, int);
	~Snake();
	//Helper methods
	void set_direction(Direction);
	void set_speed(const int&);
	Direction get_direction();
	int get_speed() const;
	snake_container* get_body();
	sf::Vector2i get_position() const;
	int get_lives() const;
	int get_score() const;
	void increase_score();
	bool has_lost() const;

	void lose();
	void toggle_lost();

	void extend();
	void reset();

	void move();
	void tick();
	void cut(int);
	void render(sf::RenderWindow&);
private:
	void check_collision();
	void check_collision_with_wall();
	snake_container m_body;
	Direction m_curr_direction;
	int m_size;
	int m_speed;
	int m_lives;
	int m_score;
	int m_grid_x_size;
	int m_grid_y_size;
	int m_block_size;
	bool m_lost;
	sf::RectangleShape m_body_rect;
};
