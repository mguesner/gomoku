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
	auto color = WHITE;
	while (1)
	{
		game.Display();
		std::cin >> x;
		std::cin >> y;
		try
		{
			if (!game.Play(x, y, color))
				std::cout << "wrong move" << std::endl;
			else
				color = (color == WHITE ? BLACK : WHITE);
		}
		catch (std::exception *e)
		{
			game.Display();
			std::cout << e->what() << std::endl;
		}
	}
}
