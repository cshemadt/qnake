#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
struct SnakeSegment{
	sf::Vector2i position;
	SnakeSegment(int x, int y) : position(x,y){}; 
};
enum Direction{ None, Up, Down, Left, Right};
class Snake{
	using snake_container = std::vector<SnakeSegment>;	
public:
	Snake(int);
	~Snake();
	//Helper methods
	void set_direction(Direction);
	Direction get_direction() const;
	int get_speed() const;
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
	snake_container m_body;
	Direction m_curr_direction;
	int m_size;
	int m_speed;
	int m_lives;
	int m_score;
	bool m_lost;
	sf::RectangleShape m_body_rect;
};
