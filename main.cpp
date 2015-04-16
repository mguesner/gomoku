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
	// int x, y;
	auto color = WHITE;
	win->Draw();
	while (1)
	{
		// std::cin >> x;
		// std::cin >> y;
		auto input = win->GetInput();
		if (input.GetType() == MOUSE)
		{
			try
			{
				if (!game.Play(input.GetX(), input.GetY(), color))
					std::cout << "wrong move" << std::endl;
				else
					color = (color == WHITE ? BLACK : WHITE);
			}
			catch (std::exception *e)
			{
				game.Display();
				std::cout << e->what() << std::endl;
			}
			win->Draw();
		}
	}
}
