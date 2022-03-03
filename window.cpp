#include "window.h"
Window::Window(const std::string& title,
               const sf::Vector2u& size) {
    setup(title,size);
}
Window::Window(){
    setup("Window", sf::Vector2u(640,480));
}
Window::~Window() {
    destroy();
}
void Window::setup(const std::string &title,
                   const sf::Vector2u& size) {
    m_window_size = size;
    m_window_title = title;
    m_is_fullscreen = false;
    m_is_done = false;
    m_window.setFramerateLimit(60);
    create();
}
void Window::create() {
    auto style=m_is_fullscreen ? sf::Style::Fullscreen : sf::Style::Default;
    sf::VideoMode video_mode{m_window_size.x,m_window_size.y,32};
    m_window.create(video_mode,m_window_title,style);
}
void Window::destroy() {
    m_window.close();
}
void Window::update() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if(event.type == sf::Event::Closed){
            m_is_done=true;
        }
        else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5){
            toggle_fullscreen();
        }
    }
}
void Window::toggle_fullscreen() {
    m_is_fullscreen=!m_is_fullscreen;
    destroy();
    create();
}
void Window::begin_draw() {
    m_window.clear(sf::Color::Black);
}
void Window::end_draw() {
    m_window.display();
}
void Window::draw(sf::Drawable &drawable) {
    m_window.draw(drawable);
}
sf::Vector2u Window::get_window_size() const {
    return m_window_size;
}
std::string Window::get_window_title() const {
    return m_window_title;
}
bool Window::is_done() const {
    return m_is_done;
}
bool Window::is_fullscreen() const {
    return m_is_fullscreen;
}
sf::RenderWindow* Window::get_render_window(){
    return &m_window;
}