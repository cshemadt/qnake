#pragma once
#include <SFML/Graphics.hpp>
class Window {
private:
    void setup(const std::string& title, const sf::Vector2u& size);
    void destroy();
    void create();
    sf::RenderWindow m_window;
    sf::Vector2u m_window_size;
    std::string m_window_title;
    bool m_is_done;
    bool m_is_fullscreen;
public:
    //Constructors & destructor
    Window();
    Window(const std::string& title, const sf::Vector2u& size);
    ~Window();

    void begin_draw(); // Clear the window
    void end_draw(); // Display the changes
    void update();

    bool is_done() const;
    bool is_fullscreen() const;

    sf::Vector2u get_window_size() const;
    std::string get_window_title() const;
    sf::RenderWindow* get_render_window();
    void toggle_fullscreen();
    void draw(sf::Drawable& drawable);
};
