#include "textbox.h"
#include <SFML/Graphics.hpp>
Textbox::Textbox(){
    setup(1,25,100, sf::Vector2f(0,0));
}
Textbox::Textbox(int visible, int font_size, int width, const sf::Vector2f &screen_pos) {
    setup(visible, font_size, width, screen_pos);
}
void Textbox::setup(int visible, int font_size, int width, const sf::Vector2f &screen_pos){
    num_visible = visible;
    sf::Vector2f offset(2.0f,2.0f);
    m_font.loadFromFile("../src/Terminess.ttf");
    m_content.setFont(m_font);
    m_content.setString("");
    m_content.setCharacterSize(font_size);
    m_content.setPosition(screen_pos+offset);
    m_content.setColor(sf::Color::White);
}
void Textbox::add(const std::string &message){ m_messages.push_back(message); }
void Textbox::clear(){ m_messages.clear(); }
void Textbox::render(sf::RenderWindow& window, int score){
    // std::string content;
    // for(auto &itr:m_messages){
    //     content.append(itr+'\n');
    // }
    // if(content!=""){
    //     m_content.setString();
    m_content.setString("Score " + std::to_string(score));
    window.draw(m_content);
    //}
}
Textbox::~Textbox(){ clear(); }