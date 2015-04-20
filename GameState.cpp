#include "GameState.hpp"

GameState::GameState()
{
	nbCaptWhite = 0;
	nbCaptBlack = 0;
	for (int i = 0; i < 19; ++i)
	{
		for (int j = 0; j < 19; ++j)
		{
			map[i][j] = NONE;
		}
	}
}

GameState::GameState(eState real[19][19], Input test, int blackcpt, int whitecpt, eState oldColor)
{
	move = test;
	(void)real;
	//map = real; // !!! MEMCPY
	//APPLIQUER LE MOVE sur map jamais modifier real (CONST ??? :D)
	//heuristic = HeuristicOfMovementForADeathBeforeLife();
	nbCaptBlack = blackcpt;
	nbCaptWhite = whitecpt;
	currentColor = oldColor == BLACK ? WHITE : BLACK;
}

GameState::GameState(GameState const & src)
{
	coups = src.coups;
	// map;
	nbCaptBlack = src.nbCaptBlack;
	nbCaptWhite = src.nbCaptWhite;
	currentColor = src.currentColor;
	heuristic = src.heuristic;
	move = src.move;
}

void GameState::GameStart()
{
	map[9][9] = BLACK;
	coups.insert(Point(8, 9, 0));
	coups.insert(Point(8, 8, 0));
	coups.insert(Point(8, 10, 0));
	coups.insert(Point(10, 8, 0));
	coups.insert(Point(10, 10, 0));
	coups.insert(Point(9, 8, 0));
	coups.insert(Point(10, 9, 0));
	coups.insert(Point(9, 10, 0));
}

bool GameState::checkThree(int x, int y, eState color)
{
	eState opponent = (color == BLACK ? WHITE : BLACK);
	int nbThrees = 0;
	int j = 0;
	int i = 1;
	int none = 0;
	while (x - i >= 0 && i < 4)
	{
		if (map[y][x - i] == color)
			j++;
		else if (map[y][x - i] == opponent && none < 1)
		{
			j = -10;
			break;
		}
		else if (map[y][x - i] == opponent || (none == 1 && map[y][x - i] == NONE))
			break;
		else if (map[y][x - i] == NONE)
			none++;
		i++;
	}
	i = 1;
	while (x + i < 19 && i < 4)
	{
		if (map[y][x + i] == color)
			j++;
		else if (map[y][x + i] == opponent && none < 2)
		{
			j = -10;
			break;
		}
		else if (map[y][x + i] == opponent || (none == 2 && map[y][x + i] == NONE))
			break;
		else if (map[y][x + i] == NONE)
			none++;
		i++;
	}
	if (j == 2)
		nbThrees++;

	i = 1;
	j = 0;
	none = 0;
	while (y - i >= 0 && i < 4)
	{
		if (map[y - i][x] == color)
			j++;
		else if (map[y - i][x] == opponent && none < 1)
		{
			j = -10;
			break;
		}
		else if (map[y - i][x] == opponent || (none == 1 && map[y - i][x] == NONE))
			break;
		else if (map[y - i][x] == NONE)
			none++;
		i++;
	}
	i = 1;
	while (y + i < 19 && i < 4)
	{
		if (map[y + i][x] == color)
			j++;
		else if (map[y + i][x] == opponent && none < 2)
		{
			j = -10;
			break;
		}
		else if (map[y + i][x] == opponent || (none == 2 && map[y + i][x] == NONE))
			break;
		else if (map[y + i][x] == NONE)
			none++;
		i++;
	}
	if (j == 2)
		nbThrees++;

	i = 1;
	j = 0;
	none = 0;
	while (y - i >= 0 && x + i < 19 && i < 4)
	{
		if (map[y - i][x + i] == color)
			j++;
		else if (map[y - i][x + i] == opponent && none < 1)
		{
			j = -10;
			break;
		}
		else if (map[y - i][x + i] == opponent || (none == 1 && map[y - i][x + i] == NONE))
			break;
		else if (map[y - i][x + i] == NONE)
			none++;
		i++;
	}
	i = 1;
	while (y + i < 19 && x - i >= 0 && i < 4)
	{
		if (map[y + i][x - i] == color)
			j++;
		else if (map[y + i][x - i] == opponent && none < 2)
		{
			j = -10;
			break;
		}
		else if (map[y + i][x - i] == opponent || (none == 2 && map[y + i][x - i] == NONE))
			break;
		else if (map[y + i][x - i] == NONE)
			none++;
		i++;
	}
	if (j == 2)
		nbThrees++;

	i = 1;
	j = 0;
	none = 0;
	while (y - i >= 0 && x - i >= 0 && i < 4)
	{
		if (map[y - i][x - i] == color)
			j++;
		else if (map[y - i][x - i] == opponent && none < 1)
		{
			j = -10;
			break;
		}
		else if (map[y - i][x - i] == opponent || (none == 1 && map[y - i][x - i] == NONE))
			break;
		else if (map[y - i][x - i] == NONE)
			none++;
		i++;
	}
	i = 1;
	while (y + i < 19 && x + i < 19 && i < 4)
	{
		if (map[y + i][x + i] == color)
			j++;
		else if (map[y + i][x + i] == opponent && none < 2)
		{
			j = -10;
			break;
		}
		else if (map[y + i][x + i] == opponent || (none == 2 && map[y + i][x + i] == NONE))
			break;
		else if (map[y + i][x + i] == NONE)
			none++;
		i++;
	}
	if (j == 2)
		nbThrees++;

	if (nbThrees > 1)
		return false;
	return true;
}

void GameState::checkVoisin(int x, int y, eState color)
{
	(void) color;
	if (map[y - 1][x] == NONE)
		coups.insert(Point(x, y - 1, 0));
	if (map[y - 1][x - 1] == NONE)
		coups.insert(Point(x - 1, y - 1, 0));
	if (map[y - 1][x + 1] == NONE)
		coups.insert(Point(x + 1, y - 1, 0));
	if (map[y + 1][x] == NONE)
		coups.insert(Point(x, y + 1, 0));
	if (map[y + 1][x + 1] == NONE)
		coups.insert(Point(x + 1, y + 1, 0));
	if (map[y + 1][x - 1] == NONE)
		coups.insert(Point(x - 1, y + 1, 0));
	if (map[y][x + 1] == NONE)
		coups.insert(Point(x + 1, y, 0));
	if (map[y][x - 1] == NONE)
		coups.insert(Point(x - 1, y, 0));
}

eState *GameState::GetMap()
{
	return (eState *)map;
}

void GameState::checkVictoire(int x, int y, eState color)
{
	eState opponent = (color == BLACK ? WHITE : BLACK);
	int i = 1;
	int capt = 0;
	int win = 1;
	while (x - i >= 0 && i < 5)
	{
		if (map[y][x - i] == color)
		{
			if (capt == 2)
			{
				map[y][x - i + 1] = NONE;
				map[y][x - i + 2] = NONE;
				(color == BLACK ? nbCaptBlack : nbCaptWhite)++;
				if (nbCaptWhite == 5 || nbCaptBlack == 5)
					throw new VictoryException(nbCaptWhite == 5 ? WHITE : BLACK);
				break;
			}
			capt = -1;
			win++;
		}
		else if (map[y][x - i] == opponent)
		{
			capt++;
		}
		i++;
	}
	if (win == 5)
		throw new VictoryException(color);
	capt = 0;
	win = 1;
	i = 1;
	while (y - i >= 0 && i < 5)
	{
		if (map[y - i][x] == color)
		{
			if (capt == 2)
			{
				map[y - i + 1][x] = NONE;
				map[y - i + 2][x] = NONE;
				(color == BLACK ? nbCaptBlack : nbCaptWhite)++;
				if (nbCaptWhite == 5 || nbCaptBlack == 5)
					throw new VictoryException(nbCaptWhite == 5 ? WHITE : BLACK);
				break;
			}
			capt = -1;
			win++;
		}
		else if (map[y - i][x] == opponent)
		{
			capt++;
		}
		i++;
	}
	if (win == 5)
		throw new VictoryException(color);
	capt = 0;
	win = 1;
	i = 1;
	while (x - i >= 0 && y - i >= 0 && i < 5)
	{
		if (map[y - i][x - i] == color)
		{
			if (capt == 2)
			{
				map[y - i + 1][x - i + 1] = NONE;
				map[y - i + 2][x - i + 2] = NONE;
				(color == BLACK ? nbCaptBlack : nbCaptWhite)++;
				if (nbCaptWhite == 5 || nbCaptBlack == 5)
					throw new VictoryException(nbCaptWhite == 5 ? WHITE : BLACK);
				break;
			}
			capt = -1;
			win++;
		}
		else if (map[y - i][x - i] == opponent)
		{
			capt++;
		}
		i++;
	}
	if (win == 5)
		throw new VictoryException(color);
	capt = 0;
	win = 1;
	i = 1;
	while (x + i < 19 && i < 5)
	{
		if (map[y][x + i] == color)
		{
			if (capt == 2)
			{
				map[y][x + i - 1] = NONE;
				map[y][x + i - 2] = NONE;
				(color == BLACK ? nbCaptBlack : nbCaptWhite)++;
				if (nbCaptWhite == 5 || nbCaptBlack == 5)
					throw new VictoryException(nbCaptWhite == 5 ? WHITE : BLACK);
				break;
			}
			capt = -1;
			win++;
		}
		else if (map[y][x + i] == opponent)
		{
			capt++;
		}
		i++;
	}
	if (win == 5)
		throw new VictoryException(color);
	capt = 0;
	win = 1;
	i = 1;
	while (y + i < 19 && i < 5)
	{
		if (map[y + i][x] == color)
		{
			if (capt == 2)
			{
				map[y + i - 1][x] = NONE;
				map[y + i - 2][x] = NONE;
				(color == BLACK ? nbCaptBlack : nbCaptWhite)++;
				if (nbCaptWhite == 5 || nbCaptBlack == 5)
					throw new VictoryException(nbCaptWhite == 5 ? WHITE : BLACK);
				break;
			}
			capt = -1;
			win++;
		}
		else if (map[y + i][x] == opponent)
		{
			capt++;
		}
		i++;
	}
	if (win == 5)
		throw new VictoryException(color);
	capt = 0;
	win = 1;
	i = 1;
	while (x + i < 19 && y + i < 19 && i < 5)
	{
		if (map[y + i][x + i] == color)
		{
			if (capt == 2)
			{
				map[y + i - 1][x + i - 1] = NONE;
				map[y + i - 2][x + i - 2] = NONE;
				(color == BLACK ? nbCaptBlack : nbCaptWhite)++;
				if (nbCaptWhite == 5 || nbCaptBlack == 5)
					throw new VictoryException(nbCaptWhite == 5 ? WHITE : BLACK);
				break;
			}
			capt = -1;
			win++;
		}
		else if (map[y + i][x + i] == opponent)
		{
			capt++;
		}
		i++;
	}
	if (win == 5)
		throw new VictoryException(color);
	capt = 0;
	win = 1;
	i = 1;
	while (x - i > 0 && y + i < 19 && i < 5)
	{
		if (map[y + i][x - i] == color)
		{
			if (capt == 2)
			{
				map[y + i - 1][x - i + 1] = NONE;
				map[y + i - 2][x - i + 2] = NONE;
				(color == BLACK ? nbCaptBlack : nbCaptWhite)++;
				if (nbCaptWhite == 5 || nbCaptBlack == 5)
					throw new VictoryException(nbCaptWhite == 5 ? WHITE : BLACK);
				break;
			}
			capt = -1;
			win++;
		}
		else if (map[y + i][x - i] == opponent)
		{
			capt++;
		}
		i++;
	}
	if (win == 5)
		throw new VictoryException(color);
	capt = 0;
	win = 1;
	i = 1;
	while (x + i < 19 && y - i > 0 && i < 5 && map[y - i][x + i] == color)
	{
		if (map[y - i][x + i] == color)
		{
			if (capt == 2)
			{
				map[y - i + 1][x + i - 1] = NONE;
				map[y - i + 2][x + i - 2] = NONE;
				(color == BLACK ? nbCaptBlack : nbCaptWhite)++;
				if (nbCaptWhite == 5 || nbCaptBlack == 5)
					throw new VictoryException(nbCaptWhite == 5 ? WHITE : BLACK);
				break;
			}
			capt = -1;
			win++;
		}
		else if (map[y - i][x + i] == opponent)
		{
			capt++;
		}
		i++;
	}
	if (win == 5)
		throw new VictoryException(!color);
}

bool GameState::Play(int x, int y, eState color)
{
	if (coups.count(Point(x, y, 0)) > 0 && checkThree(x, y, color))
	{
		map[y][x] = color;
		checkVictoire(x, y, color);
		coups.erase(Point(x, y, 0));
		checkVoisin(x, y, color);
		return true;
	}
	return false;
}

bool GameState::CheckMove(int x, int y, eState color)
{
	(void)x;
	(void)y;
	(void)color;
	// if (map[y][x] == NONE && checkVoisin(x, y, color))
	// 	return true;
	return false;
}

GameState& GameState::operator=(GameState const & src)
{
	coups = src.coups;
	// map;
	nbCaptBlack = src.nbCaptBlack;
	nbCaptWhite = src.nbCaptWhite;
	currentColor = src.currentColor;
	heuristic = src.heuristic;
	move = src.move;
	return *this;
}

std::vector<GameState*> GameState::GenerateSons()
{
	std::vector<GameState*> sons;


	for (auto i = coups.begin(); i != coups.end(); ++i)
	{
		if(checkThree((*i).getX(), (*i).getY(), currentColor))
		{
			Input test(NOINPUT, (*i).getX(), (*i).getY());
			GameState *son = new GameState(map, test, nbCaptBlack, nbCaptWhite, currentColor);
			sons.push_back(son);
		}
	}
	return sons;
}

int GameState::GetHeuristic()
{
	return heuristic;
}

Input GameState::GetMove()
{
	return move;
}


GameState::~GameState()
{
}

void GameState::Display()
{
	for (int i = 0; i < 19; ++i)
	{
		for (int j = 0; j < 19; ++j)
		{
			std::cout << (map[i][j] == NONE ? "+" : (map[i][j] == BLACK ? "N" : "B"));
		}
		std::cout << std::endl;
	}
}
