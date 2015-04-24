#include "SFMLData.hpp"
#include "Gamestate.hpp"
#include "Gomoku.hpp"



int MinMax(GameState &node, int depth, int alpha, int beta, bool Me, Input *ret, bool first)
{
	if (depth == 0 || node.IsFinalState())
	{
		//*ret = node.GetMove();
		return node.GetHeuristic();
	}
	if (Me)
	{
		auto tmp = node.GenerateSons();
		auto cur = tmp.begin();
		int bestValue = DEFAULT_MY_BEST;
		int i = 0;
		while (cur != tmp.end())
		{
			// (*cur).Display();
			int value = MinMax(*cur, depth - 1, alpha, beta, false, ret, false);
				// std::cout << "value : " << value << std::endl;
			if (first && value > bestValue)
			{
				*ret = (*cur).GetMove();
			}
			bestValue = fmax(bestValue, value);
			alpha = fmax(alpha, bestValue);
			if (beta <= alpha)
				break;
			i++;
			cur++;
		}
		// std::cout <<"depth :" << depth << " nb move : " << i << std::endl;
		return bestValue;
	}
	auto tmp = node.GenerateSons();
	auto lol = tmp.end();
	auto cur = tmp.begin();
	int bestValue = DEFAULT_ENEMY_BEST;
	int i = 0;
	while (cur != tmp.end())
	{
		int value = MinMax(*cur, depth - 1, alpha, beta, true, ret, false);
		if (value < bestValue)
				lol = cur;
		bestValue = fmin(bestValue, value);
		beta = fmin(beta, bestValue);
		if (beta <= alpha)
			break;
		cur++;
		i++;
	}
		std::cout <<"depth :" << depth << " nb move : " << i << std::endl;
	return bestValue;

}




Input do_MinMax(GameState *root, Timer timeout)
{
	int depth = 2;
	int best = 0;
	int ALPHA = ALPHA_START;
	int BETA = BETA_START;
	Input ret;
	while (timeout > std::chrono::system_clock::now())
	{
		best = MinMax(*root, depth, ALPHA, BETA, true, &ret, true);
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
		 	auto runUntil = std::chrono::system_clock::now() + std::chrono::milliseconds(500);
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
				{
					std::cout << "wrong move : " << input.GetX() <<", " << input.GetY() << std::endl;
					while (1);
				}
				else
				{
					game.BrainDead();
					game.Info();
					color = (color == WHITE ? BLACK : WHITE);
					HumanTurn = !HumanTurn;
				}
			}
			catch (std::exception *e)
			{
				// game.Display();
				// std::cout << e->what() << std::endl;
				// exit(0);
				win->DrawEndMenu(e);
				while (win->GetInput().GetType() == NOINPUT);
				exit(0);
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
