#include "SFMLData.hpp"
#include "Gamestate.hpp"
#include "Gomoku.hpp"
#include "Sound.hpp"

int g_node_opens = 0;

int MinMax(GameState &node, int depth, int alpha, int beta, bool Me, Input *ret, bool first)
{
	g_node_opens++;
	if (depth == 0 || node.IsFinalState())
	{
		//std::cout << "WTF IS THAT " << depth << "LOL CASSOS " << node.IsFinalState() << std::endl;
		auto tmp = node.GetHeuristic();
		node.Undo();
		return tmp;
	}
	if (Me)
	{
		std::vector<GameState> tmp;
		node.GenerateSons(tmp);
		std::sort(tmp.begin(), tmp.end(), std::greater<GameState>());
		auto cur = tmp.begin();
		int bestValue = DEFAULT_MY_BEST;
		int i = 0;
		if (first)
			*ret = (*cur).GetMove();
		while (cur != tmp.end())
		{
			(*cur).DoMove();
			int value = MinMax(*cur, depth - 1, alpha, beta, false, ret, false);
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
		if (!first)
			node.Undo();
		return bestValue;
	}
	std::vector<GameState> tmp;
	node.GenerateSons(tmp);
	std::sort(tmp.begin(), tmp.end());
	auto cur = tmp.begin();
	int bestValue = DEFAULT_ENEMY_BEST;
	int i = 0;
	while (cur != tmp.end())
	{
		(*cur).DoMove();
		int value = MinMax(*cur, depth - 1, alpha, beta, true, ret, false);
		bestValue = fmin(bestValue, value);
		beta = fmin(beta, bestValue);
		if (beta <= alpha)
			break;
		cur++;
		i++;
	}
	node.Undo();
	return bestValue;
}

Input do_MinMax(GameState *root, Timer timeout)
{
	int depth = 2;
	int best = 0;

	Input ret;
	while (depth < 10)
	{
		auto value = std::chrono::system_clock::now();
		g_node_opens = 0;
		int ALPHA = ALPHA_START;
		int BETA = BETA_START;
		best = MinMax(*root, depth, ALPHA, BETA, true, &ret, true);
		// if (best == WIN)
		// 	break;
		auto turnValue = std::chrono::system_clock::now() - value;
		if (turnValue * root->GetCoups().size() * root->GetCoups().size() + std::chrono::system_clock::now() > timeout)
			std::cout << " BReak call after : " << turnValue.count()  << std::endl;
		depth += 2;

	}
	std::cout << "nombre coup : " << depth << " best value: " << best << " opens node : " << g_node_opens << std::endl;
	ret.SetType(MOUSE);
	return ret;
}


int main()
{
	SFMLData *win = new SFMLData();
	srand(time(NULL));

	GameState game;

	game.GameStart();
	win->SetGameState(&game);
	auto color = WHITE;
	bool HumanTurn = true;
	bool noIA = false;
	bool menu = true;
	int choice = 0;
	Sound music(5);
	music.Play();
	win->Parameters(&music);
		Input input;
	win->DrawMainMenu(input, &noIA, &choice, &menu);
	while (1)
	{
		auto lastNow = std::chrono::system_clock::now();
		auto calcTime = std::chrono::system_clock::now() - lastNow;
		if (HumanTurn || noIA || menu)
			input = win->GetInput();
		else
		{
			game.SetColor(WHITE);
			lastNow = std::chrono::system_clock::now();
			auto runUntil =  lastNow + std::chrono::milliseconds(1000);
			input = do_MinMax(&game, runUntil);
			calcTime = std::chrono::system_clock::now() - lastNow;
			std::cout << calcTime.count() / 1000 << " ms elapsed"<< std::endl;
		}
		if (menu)
		{
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
				}
				else
				{
					color = (color == WHITE ? BLACK : WHITE);
					HumanTurn = !HumanTurn;
				}
			}
			catch (std::exception *e)
			{
				win->DrawEndMenu(e);
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
