#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
using Events = std::vector<std::pair<EventType,EventInfo>>;
enum class EventType {
    KeyDown = sf::Event::KeyPressed,
    KeyUp = sf::Event::KeyReleased,
    MButtonDown = sf::Event::MouseButtonPressed,
    MButtonUp = sf::Event::MouseButtonReleased,
    MWheel = sf::Event::MouseWheelMoved,
    WindowResized = sf::Event::Resized,
    GainedFocus = sf::Event::GainedFocus,
    LostFocus = sf::Event::LostFocus,
    Closed = sf::Event::Closed,
    MouseEntered = sf::Event::MouseEntered,
    MouseLeft = sf::Event::MouseLeft,
    TextEntered = sf::Event::TextEntered,
    Keyboard = sf::Event::Count+1, Mouse
};
struct EventInfo {
    EventInfo(){ m_code = 0;}
    EventInfo(int code) : m_code(code){}
    union{
        int m_code;
    };
};
struct EventDetails{
    EventDetails(const std::string &bind_name) : m_name(bind_name){
        clear();
    }
    std::string m_name;
    sf::Vector2i m_size;
    sf::Uint32 m_text_entered;
    sf::Vector2i m_mouse;
    int m_mouse_wheel_delta;
    int m_key_code;
    void clear(){
        m_size=sf::Vector2i(0,0);
        m_text_entered=0;
        m_mouse=sf::Vector2i(0,0);
        m_mouse_wheel_delta=0;
        m_key_code=-1;
    }
};
struct Binding{
    Binding(const std::string &binding_name) : m_name(binding_name), count(0) {}

    void bind(EventType event_type, EventInfo event_info = EventInfo()){
        m_events.emplace_back(event_type,event_info);
    }
    Events m_events;
    std::string m_name;
    int count;  
    EventDetails m_details;
};