#include "SFMLData.hpp"
#include "Gamestate.hpp"
#include "Gomoku.hpp"



int MinMax(GameState &node, int depth, int *alpha, int *beta, bool Me, Input *ret)
{
	if (depth == 0)
	{
		//*ret = node.GetMove();
		return node.GetHeuristic();
	}
	if (Me)
	{
		auto tmp = node.GenerateSons();
		auto cur = tmp.begin();
		int bestValue = DEFAULT_MY_BEST;
		while (cur != tmp.end())
		{
			int value = MinMax(*cur, depth - 1, alpha, beta, false, ret);
			if (value > bestValue)
				*ret = (*cur).GetMove();
			bestValue = fmax(bestValue, value);
			*alpha = fmax(*alpha, bestValue);
			if (*beta <= *alpha)
				break;
			cur++;
		}
		std::cout << depth << "  at this level i return : " << bestValue << std::endl;
		return bestValue;
	}
	auto tmp = node.GenerateSons();
	auto lol = tmp.end();
	auto cur = tmp.begin();
	int bestValue = DEFAULT_ENEMY_BEST;
	while (cur != tmp.end())
	{
		int value = MinMax(*cur, depth - 1, alpha, beta, true, ret);
		if (value < bestValue)
				lol = cur;
		bestValue = fmin(bestValue, value);
		*beta = fmin(*beta, bestValue);
		if (*beta <= *alpha)
			break;
		cur++;
	}
	(*lol).Info();
	std::cout << depth << "  at this (opponent) level i return : " << bestValue << std::endl;
	return bestValue;

}




Input do_MinMax(GameState *root, Timer timeout)
{
	int depth = 1;
	int best = 0;
	int ALPHA = ALPHA_START;
	int BETA = BETA_START;
	Input ret;
	while (timeout > std::chrono::system_clock::now() && depth < 4)
	{
		best = MinMax(*root, depth, &ALPHA, &BETA, true, &ret);
		depth++;
		//auto john = root->GenerateSons();
		//auto lol = std::max_element(john.begin(), john.end());
		//(*lol).Info();
		//ret = (*lol).GetMove();

	}
	std::cout << depth << std::endl;
	ret.SetType(MOUSE);
	return ret;
}


int main()
{
	SFMLData *win = new SFMLData();
	GameState game;
	game.GameStart();
	win->SetGameState(&game);
	// char buff[10];
	// int x, y;
	auto color = WHITE;
	// win->Draw();
	bool HumanTurn = true;
	bool noIA = false;
	bool menu = true;
	int choice = 0;
		Input input;
	win->DrawMainMenu(input, &noIA, &choice, &menu);
	while (1)
	{
		// std::cin >> x;
		// std::cin >> y;
		if (HumanTurn || noIA || menu)
			input = win->GetInput();
		else
		{
			game.SetColor(WHITE);
		 	auto runUntil = std::chrono::system_clock::now() + std::chrono::seconds(TIMEOUT);
		 	input = do_MinMax(&game, runUntil);
		}
		if (menu)
		{
			// std::cout << "menu" << std::endl;
			if (input.GetType() != NOINPUT)
				win->DrawMainMenu(input, &noIA, &choice, &menu);
			continue;
		}
		auto type = input.GetType();
		if (type == MOUSE)
		{
			try
			{
				if (!game.Play(input.GetX(), input.GetY(), color))
					std::cout << "wrong move" << std::endl;
				else
				{
					color = (color == WHITE ? BLACK : WHITE);
					HumanTurn = !HumanTurn;
				}
			}
			catch (std::exception *e)
			{
				game.Display();
				std::cout << e->what() << std::endl;
			}
			win->Draw();
		}
		else if (type == ESC)
		{
			delete win;
			exit(0);
		}
	}
}
