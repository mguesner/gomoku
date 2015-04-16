#include "SFMLData.hpp"
#include "Gamestate.hpp"
#include <iostream>

int main()
{
	SFMLData *win = new SFMLData();
	GameState game;
	game.GameStart();
	win->SetGameState(&game);
	// char buff[10];
	int x, y;
	while (1)
	{
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
		win->Draw();
	}
}
