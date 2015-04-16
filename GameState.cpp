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

GameState::GameState(GameState const & src)
{
	(void)src;
}

void GameState::GameStart()
{
	map[9][9] = BLACK;
}

bool GameState::checkVoisin(int x, int y, eState color)
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

	return ((x > 0 && map[y][x - 1] != NONE) || (y > 0 && map[y - 1][x] != NONE)
		|| (y > 0 && x > 0 && map[y - 1][x - 1] != NONE)
		|| (x < 18 && map[y][x + 1] != NONE) || (y < 18 && map[y + 1][x] != NONE)
		|| (y < 18 && x < 18 && map[y + 1][x + 1] != NONE)
		|| (x < 18 && y > 0 && map[y - 1][x + 1] != NONE) || (y < 18 && x > 0 && map[y + 1][x - 1] != NONE));
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
					throw VictoryException(nbCaptWhite == 5 ? WHITE : BLACK);
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
	if (map[y][x] == NONE && checkVoisin(x, y, color))
	{
		map[y][x] = color;
		checkVictoire(x, y, color);
		return true;
	}
	return false;
}

GameState& GameState::operator=(GameState const & rhs)
{
	(void)rhs;
	return *this;
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
