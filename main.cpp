#include "SFMLData.hpp"
#include "Gamestate.hpp"
#include "Gomoku.hpp"
#include "Sound.hpp"


int MinMax(GameState &node, int depth, int alpha, int beta, bool Me, Input *ret, bool first)
{
	if (depth == 0 || node.IsFinalState())
	{
		// if (node.IsFinalState())
		// {
		// 		node.Display();
		// 		printf("heuristic -> %d, depth = %d\n", node.GetHeuristic(), depth);	
		// }
		auto tmp = node.GetHeuristic();
		return tmp;
	}
	if (Me)
	{
		std::vector<GameState> tmp;
		node.GenerateSons(tmp);
		std::sort(tmp.begin(), tmp.end(), std::greater<GameState>());
		auto cur = tmp.begin();
		auto chosen = cur;
		bool choose = false;
		int bestValue = DEFAULT_MY_BEST;
		int i = 0;
		if (first)
			*ret = cur->GetMove();
		while (cur != tmp.end())
		{
			int value = MinMax(*cur, depth - 1, alpha, beta, false, ret, false);
			if (first && value > bestValue)
			{
				*ret = (*cur).GetMove();
				chosen = cur;
				choose = true;
				if (cur->IsFinalState())
					break;
			}
			bestValue = fmax(bestValue, value);
			alpha = fmax(alpha, bestValue);
			if (beta <= alpha)
				break;
			i++;
			cur++;
		}
		// if (choose)
		// {
			// chosen->Display();
			// printf("heuristic -> %d, depth -> %d\n", chosen->GetHeuristic(), depth);
			// printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
		// }
		return bestValue;
	}
	std::vector<GameState> tmp;
	// printf("__node\n");
	// node.Display();
	// printf("endnode__\n");
	node.GenerateSons(tmp);
	std::sort(tmp.begin(), tmp.end());
	auto cur = tmp.begin();
	auto chosen = cur;
	int bestValue = DEFAULT_ENEMY_BEST;
	int i = 0;
	while (cur != tmp.end())
	{
		int value = MinMax(*cur, depth - 1, alpha, beta, true, ret, false);
		// cur->Display();
		// 	printf("heuristic -> %d\n", cur->GetHeuristic());
		if (value < bestValue)
			chosen = cur;
		bestValue = fmin(bestValue, value);
		beta = fmin(beta, bestValue);
		if (beta <= alpha)
			break;
		cur++;
		i++;
	}
	// printf("__chosen\n");
	// chosen->Display();
	// printf("heuristic -> %d / %d, capture -> [%d][%d] depth -> %d\n", chosen->GetHeuristic(), bestValue, chosen->nbCaptBlack, chosen->nbCaptWhite, depth);
	// printf("endchosen__\n");
	return bestValue;
}

Input do_MinMax(GameState *root, Timer timeout)
{
	int depth = 1;
	int best = 0;

	(void)timeout;
	Input ret;
	while (1 && depth < MAXDEPTH)
	{
		auto value = std::chrono::system_clock::now();
		int ALPHA = ALPHA_START;
		int BETA = BETA_START;
		best = MinMax(*root, depth, ALPHA, BETA, true, &ret, true);
		// std::cout << "depth end with " << best << std::endl;
		if (best >= WIN)
			break;
		auto turnValue = std::chrono::system_clock::now() - value;
		if (std::chrono::system_clock::now() + turnValue * 40 > timeout)
			break;
		depth += 1;
	}
	std::cout << "depth  : " << depth << " valeur heuristic: "<< best << std::endl;
	ret.SetType(MOUSE);
	return ret;
}


int main()
{
	SFMLData *win = new SFMLData();
	srand(time(NULL));
	GameState game;
	game.GameStart();
	game.SetColor(WHITE);
	win->SetGameState(&game);
	auto color = WHITE;
	bool HumanTurn = true;
	bool noIA = false;
	bool menu = true;
	int choice = 0;
	Sound music(5);
	music.Play();
	Input input;
	bool play = win->DrawMainMenu(input, &noIA, &choice, &menu);
	while (play)
	{
		auto lastNow = std::chrono::system_clock::now();
		auto calcTime = std::chrono::system_clock::now() - lastNow;
		if (HumanTurn || noIA || menu)
			input = win->GetInput();
		else
		{
			auto lastNow = std::chrono::system_clock::now();
			auto runUntil =  lastNow + std::chrono::milliseconds(450);
			input = do_MinMax(&game, runUntil);
			calcTime = std::chrono::system_clock::now() - lastNow;
			std::cout << calcTime.count() / 1000 << " ms elapsed"<< std::endl;
		}
		if (menu)
		{
			if (input.GetType() != NOINPUT)
				play = win->DrawMainMenu(input, &noIA, &choice, &menu);
			continue;
		}
		auto type = input.GetType();
		if (type == MOUSE)
		{
			bool victory = false;
			if (!game.Play(input.GetX(), input.GetY(), color, victory))
			{
				std::cout << "wrong move : " << input.GetX() <<", " << input.GetY() << std::endl;
			}
			else
			{
				color = (color == WHITE ? BLACK : WHITE);
				HumanTurn = !HumanTurn;
			}
			if (victory)
			{
				win->DrawEndMenu();
				while (win->GetInput().GetType() == NOINPUT);
				break;
			}
			win->Draw(color);
		}
		else if (type == ESC)
			break;
	}
	delete win;
	music.Stop();
	return (0);
}
