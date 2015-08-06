#include "GameState.hpp"

//TODO       "best path" while saving state add to a fix array (size == MAXDEPTH) vector of map so when going
//            we first evaluate this path
/// maj  DONE    ---  KICKER les throw exception dans check victoire 20% de perf GG l'artiste :D xoxo <3 
//  KICKER les std::set  par des vecteurs Specvector par exemple
// maj DONE ---- generate son ==> kicker le son(this) pour chaque coups --> faire un petit son.Undotheoricplay

// test en unittest == 12 en 4sec 10 en 0.5 au premier tour

GameState::GameState()
{
	nbCaptWhite = 0;
	nbCaptBlack = 0;
	nbWhiteTwoRow = 0;
	nbWhiteThreeRow = 0;
	nbWhiteFourRow = 0;
	nbWhiteFiveRow = 0;
	nbBlackTwoRow = 0;
	nbBlackThreeRow = 0;
	nbBlackFourRow = 0;
	nbBlackFiveRow = 0;
	Finalstate = false;
	for (int i = 0; i < 19; ++i)
	{
		for (int j = 0; j < 19; ++j)
		{
			map[i][j] = NONE;
		}
	}
}

GameState::GameState(eState real[19][19], Input test, int blackcpt, int whitecpt, eState turnColor)
{
	move = test;
	std::memcpy(&map, &real, sizeof(eState) * 19 * 19);
	TheoricPlay(test.GetX(), test.GetY(), turnColor);
	nbCaptBlack = blackcpt;
	nbCaptWhite = whitecpt;
	currentColor = turnColor;
}

GameState::GameState(GameState const & src)
{
	coups = src.coups;
	std::memcpy(&map, &(src.map), sizeof(eState) * 19 * 19);
	nbCaptBlack = src.nbCaptBlack;
	nbCaptWhite = src.nbCaptWhite;
	currentColor = src.currentColor;
	heuristic = src.heuristic;
	move = src.move;
	Finalstate = src.Finalstate;
	nbWhiteTwoRow = src.nbWhiteTwoRow;
	nbWhiteThreeRow = src.nbWhiteThreeRow;
	nbWhiteFourRow = src.nbWhiteFourRow;
	nbWhiteFiveRow = src.nbWhiteFiveRow;
	nbBlackTwoRow = src.nbBlackTwoRow;
	nbBlackThreeRow = src.nbBlackThreeRow;
	nbBlackFourRow = src.nbBlackFourRow;
	nbBlackFiveRow = src.nbBlackFiveRow;
}

bool	GameState::operator<(GameState const & src) const
{
	if (heuristic < src.heuristic)
		return true;
	return false;
}

bool	GameState::operator==(GameState const & src) const
{
	if (heuristic == src.heuristic)
		return true;
	return false;
}

bool	GameState::operator<=(GameState const & src) const
{
	if (heuristic <= src.heuristic)
		return true;
	return false;
}

bool	GameState::operator>=(GameState const & src) const
{
	if (heuristic >= src.heuristic)
		return true;
	return false;
}

bool	GameState::operator>(GameState const & src) const
{
	if (heuristic > src.heuristic)
		return true;
	return false;
}

void	GameState::Update(Input test, eState turnColor)
{
	move = test;
	currentColor = turnColor;
	TheoricPlay(test.GetX(), test.GetY(), turnColor);
	BrainDead();
}

//HEURISTIC FUNCTION RETURN MAX VALUE EVALUATING CURRENT PLAYER POSITION

int		GameState::BrainDead()
{
	int ret = 0;
	int allign[3][6][3] = {{{0}}};
	for (int i = 0; i < 19; ++i)
	{
		for (int j = 0; j < 19; ++j)
		{
			auto current = map[i][j];
			if (current != NONE)
			{
				if (i - 1 >= 0 && current != map[i - 1][j])
				{
					int none = 0;
					if (map[i - 1][j] == NONE)
						none++;
					int k = 0;
					while (i + k < 19 && current == map[i + k][j])
						k++;
					if (i + k < 19 && map[i + k][j] == NONE)
						none++;
					if (none > 0)
						allign[current][k > 5 ? 5 : k][none]++;
				}
				if (j - 1 >= 0 && current != map[i][j - 1])
				{
					int none = 0;
					if (map[i][j - 1] == NONE)
						none++;
					int k = 0;
					while (j + k < 19 && current == map[i][j + k])
						k++;
					if (j + k < 19 && map[i][j + k] == NONE)
						none++;
					if (none > 0)
						allign[current][k > 5 ? 5 : k][none]++;
				}
				if (i - 1 >= 0 && j - 1 >= 0 && current != map[i - 1][j - 1])
				{
					int k = 0;
					int none = 0;
					if (i - 1 >= 0 && j - 1 >= 0 && map[i - 1][j - 1] == NONE)
						none++;
					while (i + k < 19 && j + k < 19 && current == map[i + k][j + k])
						k++;
					if (i + k < 19 && j + k < 19 && map[i + k][j + k] == NONE)
						none++;
					if (none > 0)
						allign[current][k > 5 ? 5 : k][none]++;
				}
				if (i - 1 >= 0 && j + 1 < 19 && current != map[i - 1][j + 1])
				{
					int none = 0;
					if (map[i - 1][j + 1] == NONE)
						none++;
					int k = 0;
					while (i + k < 19 && j - k >= 0 && current == map[i + k][j - k])
						k++;
					if (i + k < 19 && j - k >= 0 && NONE == map[i + k][j - k])
						none++;
					if (none > 0)
						allign[current][k > 5 ? 5 : k][none]++;
				}
			}
		}
	}
	ret += allign[BLACK][2][1] * TWOROWONEWAY;
	ret += allign[BLACK][3][1] * THREEROWONEWAY;
	ret += allign[BLACK][4][1] * FOURROWONEWAY;
	ret += allign[BLACK][2][2] * TWOROWONEWAY;
	ret += allign[BLACK][3][2] * THREEROWONEWAY;
	ret += allign[BLACK][4][2] * FOURROWTWOWAY;
	if (allign[BLACK][5][1] || allign[BLACK][5][2])
	{
		Finalstate = true;
		return WIN;
	}
	ret += allign[WHITE][2][1] * ENEMYTWOONEWAY;
	ret += allign[WHITE][3][1] * ENEMYTHREEONEWAY;
	ret += allign[WHITE][4][1] * ENEMYFOUR;
	ret += allign[WHITE][2][2] * ENEMYTWOTWOWAY;
	ret += allign[WHITE][3][2] * ENEMYTHREETWOWAY;
	if (allign[WHITE][4][2])
		return LOOSE - 10;
	if (allign[WHITE][5][1] || allign[WHITE][5][2])
	{
		Finalstate = true;
		return LOOSE;
	}
	if (nbCaptBlack == 1)
		ret += CAPTUREONE + 10;
	else if (nbCaptBlack == 2)
		ret += CAPTURETWO + 10;
	else if (nbCaptBlack == 3)
		ret += CAPTURETHREE;
	else if (nbCaptBlack == 4)
		ret += CAPTUREFOUR;
	else if (nbCaptBlack >= 5)
	{
		Finalstate = true;
		return WIN;
	}

	if (nbCaptWhite == 1)
		ret -= CAPTUREONE;
	else if (nbCaptWhite == 2)
		ret -= CAPTURETWO;
	else if (nbCaptWhite == 3)
		ret -= CAPTURETHREE;
	else if (nbCaptWhite == 4)
		ret -= CAPTUREFOUR;
	else if (nbCaptWhite >= 5)
	{
		Finalstate = true;
		return LOOSE;
	}
	int alea = rand() % 5;
	heuristic = ret + alea;
	return ret;
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

	// std::cout << "(" << x<< ", " << y<< ") -> " << nbThrees << "  color : " << (color == BLACK ? "black" : "white") << std::endl;
	if (nbThrees > 1)
		return false;
	return true;
}

void GameState::checkVoisin(int x, int y, eState color)
{
	(void)color;
	if (y - 1 >= 0 && map[y - 1][x] == NONE)
		coups.insert(Point(x, y - 1, 0));
	if (y + 1 < 19 && map[y + 1][x] == NONE)
		coups.insert(Point(x, y + 1, 0));
	if (y - 1 >= 0 && x - 1 >= 0 && map[y - 1][x - 1] == NONE)
		coups.insert(Point(x - 1, y - 1, 0));
	if (y + 1 < 19 && x + 1 < 19 && map[y + 1][x + 1] == NONE)
		coups.insert(Point(x + 1, y + 1, 0));
	if (y - 1 >= 0 && x + 1 < 19 && map[y - 1][x + 1] == NONE)
		coups.insert(Point(x + 1, y - 1, 0));
	if (y + 1 < 19 && x - 1 >= 0 && map[y + 1][x - 1] == NONE)
		coups.insert(Point(x - 1, y + 1, 0));
	if (x + 1 < 19 && map[y][x + 1] == NONE)
		coups.insert(Point(x + 1, y, 0));
	if (x - 1 >= 0 && map[y][x - 1] == NONE)
		coups.insert(Point(x - 1, y, 0));
}

eState *GameState::GetMap()
{
	return (eState *)map;
}

bool GameState::isCapturable(bool *check, int x, int y, eState color)
{
	if (*check)
	{
		eState opponent = (color == BLACK ? WHITE : BLACK);
		if ((y - 1 >= 0 && y + 2 < 19 && map[y - 1][x] == opponent && map[y + 1][x] == color && map[y + 2][x] == NONE)
			|| (y + 1 < 19 && y - 2 >= 0 && map[y + 1][x] == opponent && map[y - 1][x] == color && map[y - 2][x] == NONE)
			|| (x - 1 >= 0 && x + 2 < 19 && map[y][x - 1] == opponent && map[y][x + 1] == color && map[y][x + 2] == NONE)
			|| (x - 2 >= 0 && x + 1 < 19 && map[y][x + 1] == opponent && map[y][x - 1] == color && map[y][x - 2] == NONE)
			|| (y - 1 >= 0 && x - 1 >= 0 && x + 2 < 19 && y + 2 < 19 && map[y - 1][x - 1] == opponent && map[y + 1][x + 1] == color && map[y + 2][x + 2] == NONE)
			|| (y - 2 >= 0 && x - 2 >= 0 && x + 1 < 19 && y + 1 < 19 && map[y + 1][x + 1] == opponent && map[y - 1][x - 1] == color && map[y - 2][x - 2] == NONE)
			|| (y - 1 >= 0 && x - 2 >= 0 && x + 1 < 19 && y + 2 < 19 && map[y - 1][x + 1] == opponent && map[y + 1][x - 1] == color && map[y + 2][x - 2] == NONE)
			|| (y - 2 >= 0 && x - 1 >= 0 && x + 2 < 19 && y + 1 < 19 && map[y + 1][x - 1] == opponent && map[y - 1][x + 1] == color && map[y - 2][x + 2] == NONE))
		{
			*check = false;
			return false;
		}
		return true;
	}
	return false;
}

eState GameState::checkVictoire(int x, int y, eState color)
{
	eState opponent = (color == BLACK ? WHITE : BLACK);
	int i = 1;
	int capt = 0;
	int win = 1;
	bool check = true;
	while (x - i >= 0 && i < 5)
	{
		if (map[y][x - i] == color)
		{
			if (capt == 2)
			{
				map[y][x - i + 1] = NONE;
				map[y][x - i + 2] = NONE;
				coups.insert(Point(x - i + 1, y, 0));
				coups.insert(Point(x - i + 2, y, 0));
				(color == BLACK ? nbCaptBlack : nbCaptWhite)++;
				if (nbCaptWhite == 5 || nbCaptBlack == 5)
					return nbCaptWhite == 5 ? WHITE : BLACK;
				break;
			}
			capt = -1;
			if (isCapturable(&check, x - i, y, color))
				win++;
			else
				break;
		}
		else if (map[y][x - i] == opponent)
		{
			check = false;
			capt++;
		}
		else
			break;
		i++;
	}
	capt = 0;
	i = 1;
	check = true;
	while (x + i < 19 && i < 5)
	{
		if (map[y][x + i] == color)
		{
			if (capt == 2)
			{
				map[y][x + i - 1] = NONE;
				map[y][x + i - 2] = NONE;
				coups.insert(Point(x + i - 1, y, 0));
				coups.insert(Point(x + i - 2, y, 0));
				(color == BLACK ? nbCaptBlack : nbCaptWhite)++;
				if (nbCaptWhite == 5 || nbCaptBlack == 5)
					return nbCaptWhite == 5 ? WHITE : BLACK;
				break;
			}
			capt = -1;
			if (isCapturable(&check, x + i, y, color))
				win++;
			else
				break;
		}
		else if (map[y][x + i] == opponent)
		{
			check = false;
			capt++;
		}
		else
			break;
		i++;
	}
	if (win >= 5)
		return color;

	capt = 0;
	win = 1;
	i = 1;
	check = true;
	while (y - i >= 0 && i < 5)
	{
		if (map[y - i][x] == color)
		{
			if (capt == 2)
			{
				map[y - i + 1][x] = NONE;
				map[y - i + 2][x] = NONE;
				coups.insert(Point(x, y - i + 1, 0));
				coups.insert(Point(x, y - i + 2, 0));
				(color == BLACK ? nbCaptBlack : nbCaptWhite)++;
				(color == BLACK ? nbWhiteTwoRow : nbBlackTwoRow)--;
				if (nbCaptWhite == 5 || nbCaptBlack == 5)
					return nbCaptWhite == 5 ? WHITE : BLACK;
				break;
			}
			capt = -1;
			if (isCapturable(&check, x, y - i, color))
				win++;
			else
				break;
		}
		else if (map[y - i][x] == opponent)
		{
			check = false;
			capt++;
		}
		else
			break;
		i++;
	}
	check = true;
	capt = 0;
	i = 1;
	while (y + i < 19 && i < 5)
	{
		if (map[y + i][x] == color)
		{
			if (capt == 2)
			{
				map[y + i - 1][x] = NONE;
				map[y + i - 2][x] = NONE;
				coups.insert(Point(x, y + i - 1, 0));
				coups.insert(Point(x, y + i - 2, 0));
				(color == BLACK ? nbCaptBlack : nbCaptWhite)++;
				(color == BLACK ? nbWhiteTwoRow : nbBlackTwoRow)--;
				if (nbCaptWhite == 5 || nbCaptBlack == 5)
					return nbCaptWhite == 5 ? WHITE : BLACK;
				break;
			}
			capt = -1;
			if (isCapturable(&check, x, y + i, color))
				win++;
			else
				break;
		}
		else if (map[y + i][x] == opponent)
		{
			check = false;
			capt++;
		}
		else
			break;
		i++;
	}
	if (win >= 5)
		return color;

	capt = 0;
	win = 1;
	check = true;
	i = 1;
	while (x - i >= 0 && y - i >= 0 && i < 5)
	{
		if (map[y - i][x - i] == color)
		{
			if (capt == 2)
			{
				map[y - i + 1][x - i + 1] = NONE;
				map[y - i + 2][x - i + 2] = NONE;
				coups.insert(Point(x - i + 1, y - i + 1, 0));
				coups.insert(Point(x - i + 2, y - i + 2, 0));
				(color == BLACK ? nbCaptBlack : nbCaptWhite)++;
				(color == BLACK ? nbWhiteTwoRow : nbBlackTwoRow)--;
				if (nbCaptWhite == 5 || nbCaptBlack == 5)
					return nbCaptWhite == 5 ? WHITE : BLACK;
				break;
			}
			capt = -1;
			if (isCapturable(&check, x - i, y - i, color))
				win++;
			else
				break;
		}
		else if (map[y - i][x - i] == opponent)
		{
			check = false;
			capt++;
		}
		else
			break;
		i++;
	}
	check = true;
	capt = 0;
	i = 1;
	while (x + i < 19 && y + i < 19 && i < 5)
	{
		if (map[y + i][x + i] == color)
		{
			if (capt == 2)
			{
				map[y + i - 1][x + i - 1] = NONE;
				map[y + i - 2][x + i - 2] = NONE;
				coups.insert(Point(x + i - 1, y + i - 1, 0));
				coups.insert(Point(x + i - 2, y + i - 2, 0));
				(color == BLACK ? nbCaptBlack : nbCaptWhite)++;
				(color == BLACK ? nbWhiteTwoRow : nbBlackTwoRow)--;
				if (nbCaptWhite == 5 || nbCaptBlack == 5)
					return nbCaptWhite == 5 ? WHITE : BLACK;
				break;
			}
			capt = -1;
			if (isCapturable(&check, x + i, y + i, color))
				win++;
			else
				break;
		}
		else if (map[y + i][x + i] == opponent)
		{
			check = false;
			capt++;
		}
		else
			break;
		i++;
	}
	if (win >= 5)
		return color;

	check = true;
	capt = 0;
	win = 1;
	i = 1;
	while (x - i >= 0 && y + i < 19 && i < 5)
	{
		if (map[y + i][x - i] == color)
		{
			if (capt == 2)
			{
				map[y + i - 1][x - i + 1] = NONE;
				map[y + i - 2][x - i + 2] = NONE;
				coups.insert(Point(x - i + 1, y + i - 1, 0));
				coups.insert(Point(x - i + 2, y + i - 2, 0));
				(color == BLACK ? nbCaptBlack : nbCaptWhite)++;
				(color == BLACK ? nbWhiteTwoRow : nbBlackTwoRow)--;
				if (nbCaptWhite == 5 || nbCaptBlack == 5)
					return nbCaptWhite == 5 ? WHITE : BLACK;
				break;
			}
			capt = -1;
			if (isCapturable(&check, x - i, y + i, color))
				win++;
			else
				break;
		}
		else if (map[y + i][x - i] == opponent)
		{
			check = false;
			capt++;
		}
		else
			break;
		i++;
	}
	check = true;
	capt = 0;
	i = 1;
	while (x + i < 19 && y - i >= 0 && i < 5)
	{
		if (map[y - i][x + i] == color)
		{
			if (capt == 2)
			{
				map[y - i + 1][x + i - 1] = NONE;
				map[y - i + 2][x + i - 2] = NONE;
				coups.insert(Point(x + i - 1, y - i + 1, 0));
				coups.insert(Point(x + i - 2, y - i + 2, 0));
				(color == BLACK ? nbCaptBlack : nbCaptWhite)++;
				(color == BLACK ? nbWhiteTwoRow : nbBlackTwoRow)--;
				if (nbCaptWhite == 5 || nbCaptBlack == 5)
					return nbCaptWhite == 5 ? WHITE : BLACK;
				break;
			}
			capt = -1;
			if (isCapturable(&check, x + i, y - i, color))
				win++;
			else
				break;
		}
		else if (map[y - i][x + i] == opponent)
		{
			check = false;
			capt++;
		}
		else
			break;
		i++;
	}
	if (win >= 5)
		return color;
	return NONE;
}

void GameState::checkVictoireCrazy(int x, int y, eState color)
{
	eState opponent = (color == BLACK ? WHITE : BLACK);
	int i = 1;
	int capt = 0;
	int win = 1;
	bool check = true;
	while (x - i >= 0 && i < 5)
	{
		if (map[y][x - i] == color)
		{
			if (capt == 2)
			{
				map[y][x - i + 1] = NONE;
				map[y][x - i + 2] = NONE;
				coups.insert(Point(x - i + 1, y, 0));
				coups.insert(Point(x - i + 2, y, 0));
				(color == BLACK ? nbCaptBlack : nbCaptWhite)++;
				break;
			}
			capt = -1;
			if (check)
				win++;
		}
		else if (map[y][x - i] == opponent)
		{
			check = false;
			capt++;
		}
		i++;
	}
	check = true;
	capt = 0;
	i = 1;
	while (x + i < 19 && i < 5)
	{
		if (map[y][x + i] == color)
		{
			if (capt == 2)
			{
				map[y][x + i - 1] = NONE;
				map[y][x + i - 2] = NONE;
				coups.insert(Point(x + i - 1, y, 0));
				coups.insert(Point(x + i - 2, y, 0));
				(color == BLACK ? nbCaptBlack : nbCaptWhite)++;
				(color == BLACK ? nbWhiteTwoRow : nbBlackTwoRow)--;
				break;
			}
			capt = -1;
			if (check)
				win++;
		}
		else if (map[y][x + i] == opponent)
		{
			check = false;
			capt++;
		}
		i++;
	}
	if (win >= 5)
		Finalstate = true;

	capt = 0;
	win = 1;
	i = 1;
	check = true;
	while (y - i >= 0 && i < 5)
	{
		if (map[y - i][x] == color)
		{
			if (capt == 2)
			{
				map[y - i + 1][x] = NONE;
				map[y - i + 2][x] = NONE;
				coups.insert(Point(x, y - i + 1, 0));
				coups.insert(Point(x, y - i + 2, 0));
				(color == BLACK ? nbCaptBlack : nbCaptWhite)++;
				(color == BLACK ? nbWhiteTwoRow : nbBlackTwoRow)--;
				break;
			}
			capt = -1;
			if (check)
				win++;
		}
		else if (map[y - i][x] == opponent)
		{
			check = false;
			capt++;
		}
		i++;
	}
	capt = 0;
	i = 1;
	check = true;
	while (y + i < 19 && i < 5)
	{
		if (map[y + i][x] == color)
		{
			if (capt == 2)
			{
				map[y + i - 1][x] = NONE;
				map[y + i - 2][x] = NONE;
				coups.insert(Point(x, y + i - 1, 0));
				coups.insert(Point(x, y + i - 2, 0));
				(color == BLACK ? nbCaptBlack : nbCaptWhite)++;
				(color == BLACK ? nbWhiteTwoRow : nbBlackTwoRow)--;
				break;
			}
			capt = -1;
			if (check)
				win++;
		}
		else if (map[y + i][x] == opponent)
		{
			check = false;
			capt++;
		}
		i++;
	}
	if (win >= 5)
		Finalstate = true;

	capt = 0;
	win = 1;
	i = 1;
	check = true;
	while (x - i >= 0 && y - i >= 0 && i < 5)
	{
		if (map[y - i][x - i] == color)
		{
			if (capt == 2)
			{
				map[y - i + 1][x - i + 1] = NONE;
				map[y - i + 2][x - i + 2] = NONE;
				coups.insert(Point(x - i + 1, y - i + 1, 0));
				coups.insert(Point(x - i + 2, y - i + 2, 0));
				(color == BLACK ? nbCaptBlack : nbCaptWhite)++;
				(color == BLACK ? nbWhiteTwoRow : nbBlackTwoRow)--;
				break;
			}
			capt = -1;
			if (check)
				win++;
		}
		else if (map[y - i][x - i] == opponent)
		{
			check = false;
			capt++;
		}
		i++;
	}
	capt = 0;
	i = 1;
	check = true;
	while (x + i < 19 && y + i < 19 && i < 5)
	{
		if (map[y + i][x + i] == color)
		{
			if (capt == 2)
			{
				map[y + i - 1][x + i - 1] = NONE;
				map[y + i - 2][x + i - 2] = NONE;
				coups.insert(Point(x + i - 1, y + i - 1, 0));
				coups.insert(Point(x + i - 2, y + i - 2, 0));
				(color == BLACK ? nbCaptBlack : nbCaptWhite)++;
				(color == BLACK ? nbWhiteTwoRow : nbBlackTwoRow)--;
				break;
			}
			capt = -1;
			if (check)
				win++;
		}
		else if (map[y + i][x + i] == opponent)
		{
			check = false;
			capt++;
		}
		i++;
	}
	if (win >= 5)
		Finalstate = true;

	capt = 0;
	win = 1;
	i = 1;
	check = true;
	while (x - i > 0 && y + i < 19 && i < 5)
	{
		if (map[y + i][x - i] == color)
		{
			if (capt == 2)
			{
				map[y + i - 1][x - i + 1] = NONE;
				map[y + i - 2][x - i + 2] = NONE;
				coups.insert(Point(x - i + 1, y + i - 1, 0));
				coups.insert(Point(x - i + 2, y + i - 2, 0));
				(color == BLACK ? nbCaptBlack : nbCaptWhite)++;
				(color == BLACK ? nbWhiteTwoRow : nbBlackTwoRow)--;
				break;
			}
			capt = -1;
			if (check)
				win++;
		}
		else if (map[y + i][x - i] == opponent)
		{
			check = false;
			capt++;
		}
		i++;
	}
	capt = 0;
	i = 1;
	check = true;
	while (x + i < 19 && y - i > 0 && i < 5)
	{
		if (map[y - i][x + i] == color)
		{
			if (capt == 2)
			{
				map[y - i + 1][x + i - 1] = NONE;
				map[y - i + 2][x + i - 2] = NONE;
				coups.insert(Point(x + i - 1, y - i + 1, 0));
				coups.insert(Point(x + i - 2, y - i + 2, 0));
				(color == BLACK ? nbCaptBlack : nbCaptWhite)++;
				(color == BLACK ? nbWhiteTwoRow : nbBlackTwoRow)--;
				break;
			}
			capt = -1;
			if (check)
				win++;
		}
		else if (map[y - i][x + i] == opponent)
		{
			check = false;
			capt++;
		}
		i++;
	}
	if (win >= 5)
		Finalstate = true;
}

bool GameState::Play(int x, int y, eState color)
{
	if (coups.count(Point(x, y, 0)) > 0 && !coups.find(Point(x, y, 0))->IsForbiden(color))
	{
		map[y][x] = color;
		checkVictoire(x, y, color);
		coups.erase(Point(x, y, 0));
		checkVoisin(x, y, color);
		std::set<Point> patate;
		for (auto i = coups.begin(); i != coups.end(); ++i)
		{
			// if ((*i).IsForbiden(color == WHITE ? BLACK : WHITE))
			// 	std::cout << "FORBIDDEN" << std::endl;
			Point tmp(*i);
			// std::cout << "copie -> (" << tmp.getX() << ", " << tmp.getY() << ")" << std::endl;
			if (!checkThree((*i).getX(), (*i).getY(), color))
				tmp.Forbiden(color, true);
			else
				tmp.Forbiden(color, false);
			//coups.erase(*i);
			patate.insert(tmp);
		}
		coups.clear();
		coups.insert(patate.begin(), patate.end());
		return true;
	}
	return false;
}

bool GameState::TheoricPlay(int x, int y, eState color)
{
	if (coups.count(Point(x, y, 0)) > 0 && !coups.find(Point(x, y, 0))->IsForbiden(color))
	{
		map[y][x] = color;
		if (checkVictoire(x, y, color) != NONE)
			Finalstate = true;
		coups.erase(Point(x, y, 0));
		checkVoisin(x, y, color);
		theoricPlay = true;
		return true;
	}
	return false;
}

void GameState::UndoTheoricPlay()
{
	if (!theoricPlay)
		return;
	int x = move.GetX();
	int y = move.GetY();
	map[y][x] = NONE;
	coups.insert(Point(move.GetX(), move.GetY(), 0));
	theoricPlay = false;
}

bool GameState::CheckMove(int x, int y, eState color)
{
	(void)x;
	(void)y;
	(void)color;
	std::cout << "heulol" << std::endl;
	// if (map[y][x] == NONE && checkVoisin(x, y, color))
	// 	return true;
	return false;
}

GameState& GameState::operator=(GameState const & src)
{
	coups = src.coups;
	std::memcpy(&map, &(src.map), sizeof(eState) * 19 * 19);
	nbCaptBlack = src.nbCaptBlack;
	nbCaptWhite = src.nbCaptWhite;
	currentColor = src.currentColor;
	heuristic = src.heuristic;
	move = src.move;
	nbWhiteTwoRow = src.nbWhiteTwoRow;
	nbWhiteThreeRow = src.nbWhiteThreeRow;
	nbWhiteFourRow = src.nbWhiteFourRow;
	nbWhiteFiveRow = src.nbWhiteFiveRow;
	nbBlackTwoRow = src.nbBlackTwoRow;
	nbBlackThreeRow = src.nbBlackThreeRow;
	nbBlackFourRow = src.nbBlackFourRow;
	nbBlackFiveRow = src.nbBlackFiveRow;
	return *this;
}

void GameState::GenerateSons(std::vector<GameState> &sons)
{
	sons.reserve(coups.size());
	auto reverse = (currentColor == WHITE ? BLACK : WHITE);
	//GameState son(*this);
	for (auto i = coups.begin(); i != coups.end(); ++i)
	{
		if(!i->IsForbiden(currentColor))
		{
			Input test(NOINPUT, (*i).getX(), (*i).getY());
			GameState son(*this);
			son.Update(test, reverse);
			sons.push_back(son);
			//son.Undo();
		}
	}
}

int GameState::GetHeuristic()
{
	return heuristic;
}

std::set<Point> GameState::GetCoups()
{
	return coups;
}

Input GameState::GetMove()
{
	return move;
}

void GameState::SetColor(eState color)
{
	currentColor = color;
}

bool GameState::IsFinalState() const
{
	if (nbCaptWhite == 5 || nbCaptBlack == 5)
		return true;
	return Finalstate;
}

GameState::~GameState()
{
}

int GameState::GetCapture(eState color)
{
	return (color == WHITE ? nbCaptWhite : nbCaptBlack);
}

void GameState::Info()
{
	std::cout << "This map is value at : " << heuristic << std::endl;
}

void GameState::Display() const
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
