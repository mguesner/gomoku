#include "SFMLData.hpp"
#include "Gamestate.hpp"
#include <iostream>

int main()
{
	// SFMLData *win = new SFMLData();
	// (void)win;
	GameState game;
	game.GameStart();
	// char buff[10];
	int x, y;
	while (1)
	{
		game.Display();
		std::cin >> x;
		std::cin >> y;
		try
		{
			if (!game.Play(x, y, BLACK))
				std::cout << "wrong move" << std::endl;
		}
		catch (std::exception *e)
		{
			std::cout << e->what() << std::endl;
		}
	}
}
