#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
using message_container = std::vector<std::string>;

class Textbox{
public:    
    Textbox();
    Textbox(int visible, int font_size, int width, const sf::Vector2f &screen_pos);
    ~Textbox();
    void setup(int visible, int font_size, int width, const sf::Vector2f &screen_pos);
    void add(const std::string &message);
    void clear();
    void render(sf::RenderWindow &window, int);
private:
    message_container m_messages;
    int num_visible;
    sf::RectangleShape m_backdrop;
    sf::Font m_font;
    sf::Text m_content;
};
