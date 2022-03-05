#include <SFML/Graphics.hpp>
#include "game.h"
#include <iostream>
int main()
{
    Game game{};
	while(!game.get_window()->is_done()){
        game.handle_input();
        game.update();
		game.render();
        game.restart_clock();
    }
    return 0;
}
