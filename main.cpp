#include <SFML/Graphics.hpp>
#include "game.h"
#include <iostream>
int main()
{
    Game game{};
	while(!game.get_window()->is_done()){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) && sf::Keyboard::isKeyPressed(sf::Keyboard::F4)){
            return 0;
        }
        game.handle_input();
        game.update();
		game.render();
        game.restart_clock();
    }
    return 0;
}
