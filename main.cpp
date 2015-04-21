#include "SFMLData.hpp"
#include "Gamestate.hpp"
#include "Gomoku.hpp"



int MinMax(GameState *node, int depth, int *alpha, int *beta, bool Me, Input *ret)
{
	if (depth == 0)
	{
		*ret = node->GetMove();
		return node->GetHeuristic();
	}
	if (Me)
	{
		auto tmp = node->GenerateSons();
		auto cur = tmp.begin();
		int bestValue = DEFAULT_MY_BEST;
		while (cur != tmp.end())
		{
			int value = MinMax(*cur, depth - 1, alpha, beta, false, ret);
			bestValue = fmax(bestValue, value);
			*alpha = fmax(*alpha, bestValue);
			if (*beta <= *alpha)
				break;
			cur++;
		}
		return bestValue;
	}
	auto tmp = node->GenerateSons();
	auto cur = tmp.begin();
	int bestValue = DEFAULT_ENEMY_BEST;
	while (cur != tmp.end())
	{
		int value = MinMax(*cur, depth - 1, alpha, beta, true, ret);
		bestValue = fmin(bestValue, value);
		*beta = fmin(*beta, bestValue);
		if (*beta <= *alpha)
			break;
		cur++;
	}
	return bestValue;

}




Input do_MinMax(GameState *root, Timer timeout)
{
	// int depth = 1;
	// int best = 0;
	// int ALPHA = ALPHA_START;
	// int BETA = BETA_START;
	Input ret;
	(void)timeout;
	//while (timeout < std::chrono::system_clock::now())
	//{
		//best = MinMax(root, depth, &ALPHA, &BETA, true, &ret);
		auto john = root->GenerateSons();
		auto lol = std::max_element(john.begin(), john.end());
		//depth++;
		// do timeout-- or be sure it will.
	//}
	ret = (*lol)->GetMove();
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
	win->Draw();
	bool HumanTurn = true;
	bool noIA = false;
	while (1)
	{
		// std::cin >> x;
		// std::cin >> y;

		Input input;
		if (HumanTurn || noIA)
			input = win->GetInput();
		else
		{
			game.SetColor(WHITE);
		 	auto runUntil = std::chrono::system_clock::now() + std::chrono::seconds(TIMEOUT);
		 	input = do_MinMax(&game, runUntil);
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
			exit(0);
	}
}
