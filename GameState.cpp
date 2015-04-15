#include "GameState.hpp"

GameState::GameState()
{
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

bool GameState::checkVoisin(int x, int y)
{
	return ((x > 0 && map[y][x - 1] != NONE) || (y > 0 && map[y - 1][x] != NONE)
		|| (y > 0 && x > 0 && map[y - 1][x - 1] != NONE)
		|| (x < 18 && map[y][x + 1] != NONE) || (y < 18 && map[y + 1][x] != NONE)
		|| (y < 18 && x < 18 && map[y + 1][x + 1] != NONE)
		|| (x < 18 && y > 0 && map[y - 1][x + 1] != NONE) || (y < 18 && x > 0 && map[y + 1][x - 1] != NONE));
}

void GameState::checkVictoire(int x, int y, eState color)
{
	eState opponent = (color == BLACK ? WHITE : BLACK);
	int i = 0;
	int capt = 0;
	int win = 0;
	while (x - i >= 0 && i < 5)
	{
		if (map[y][x - i] == color)
		{
			if (capt == 2)
			{
				map[y][x - i + 1] = NONE;
				map[y][x - i + 2] = NONE;
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
	win = 0;
	i = 0;
	while (y - i >= 0 && i < 5)
	{
		if (map[y - i][x] == color)
		{
			if (capt == 2)
			{
				map[y - i + 1][x] = NONE;
				map[y - i + 2][x] = NONE;
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
	win = 0;
	i = 0;
	while (x - i >= 0 && y - i >= 0 && i < 5)
	{
		if (map[y - i][x - i] == color)
		{
			if (capt == 2)
			{
				map[y - i + 1][x - i + 1] = NONE;
				map[y - i + 2][x - i + 2] = NONE;
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
	win = 0;
	i = 0;
	while (x + i < 19 && i < 5)
	{
		if (map[y][x + i] == color)
		{
			if (capt == 2)
			{
				map[y][x + i - 1] = NONE;
				map[y][x + i - 2] = NONE;
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
	win = 0;
	i = 0;
	while (y + i < 19 && i < 5)
	{
		if (map[y + i][x] == color)
		{
			if (capt == 2)
			{
				map[y + i - 1][x] = NONE;
				map[y + i - 2][x] = NONE;
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
	win = 0;
	i = 0;
	while (x + i < 19 && y + i < 19 && i < 5)
	{
		if (map[y + i][x + i] == color)
		{
			if (capt == 2)
			{
				map[y + i - 1][x + i - 1] = NONE;
				map[y + i - 2][x + i - 2] = NONE;
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
	win = 0;
	i = 0;
	while (x - i > 0 && y + i < 19 && i < 5)
	{
		if (map[y + i][x - i] == color)
		{
			if (capt == 2)
			{
				map[y + i - 1][x - i + 1] = NONE;
				map[y + i - 2][x - i + 2] = NONE;
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
	win = 0;
	i = 0;
	while (x + i < 19 && y - i > 0 && i < 5 && map[y - i][x + i] == color)
	{
		if (map[y - i][x + i] == color)
		{
			if (capt == 2)
			{
				map[y - i + 1][x + i - 1] = NONE;
				map[y - i + 2][x + i - 2] = NONE;
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

void GameState::checkCapture(int x, int y, eState color)
{
	int i = 0;
	while (x - i >= 0 && i < 2 && map[y][x - i] == !color)
		i++;
	if (i == 2 && x - i >= 0 && map[y][x - i] == color)
	{
		map[y][x - i + 1] = NONE;
		map[y][x - i + 2] = NONE;
	}
	i = 0;
	while (y - i >= 0 && i < 2 && map[y - i][x] == !color)
		i++;
	if (i == 2)
		throw new VictoryException(!color);
	i = 0;
	while (x - i >= 0 && y - i >= 0 && i < 2 && map[y - i][x - i] == !color)
		i++;
	if (i == 2)
		throw new VictoryException(!color);
	i = 0;
	while (x + i < 19 && i < 2 && map[y][x + i] == !color)
		i++;
	if (i == 2)
		throw new VictoryException(!color);
	i = 0;
	while (y + i < 19 && i < 2 && map[y + i][x] == !color)
		i++;
	if (i == 2)
		throw new VictoryException(!color);
	i = 0;
	while (x + i < 19 && y + i < 19 && i < 2 && map[y + i][x + i] == !color)
		i++;
	if (i == 2)
		throw new VictoryException(!color);
	i = 0;
	while (x - i > 0 && y + i < 19 && i < 2 && map[y + i][x - i] == !color)
		i++;
	if (i == 2)
		throw new VictoryException(!color);
	i = 0;
	while (x + i < 19 && y - i > 0 && i < 2 && map[y - i][x + i] == !color)
		i++;
	if (i == 2)
		throw new VictoryException(!color);
}

bool GameState::Play(int x, int y, eState color)
{
	if (map[y][x] == NONE && checkVoisin(x, y))
	{
		map[y][x] = color;
		// checkCapture(x, y, color);
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
