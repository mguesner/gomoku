#include "GameState.hpp"

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
	heuristic = BrainDead();
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
	heuristic = BrainDead();
}

//HEURISTIC FUNCTION RETURN MAX VALUE EVALUATING CURRENT PLAYER POSITION

int		GameState::BrainDead()
{
	int ret = 0;
	//auto opponentColor = (currentColor == WHITE ? BLACK : WHITE);
	int allign[3][6] = {{0}};
	int capt[3] = {0};
	for (int i = 0; i < 19; ++i)
	{
		for (int j = 0; j < 19; ++j)
		{
			auto current = map[i][j];
			if (current != NONE)
			{
				if (i - 1 >= 0 && current != map[i - 1][j])
				{
					int k = 0;
					while (i + k < 19 && current == map[i + k][j])
						k++;
					allign[current][k > 5 ? 5 : k]++;
					if (k == 2 && map[i - 1][j] != NONE && map[i + k][j] == NONE)
						capt[current]++;
				}
				if (j - 1 >= 0 && current != map[i][j - 1])
				{
					int k = 0;
					while (j + k < 19 && current == map[i][j + k])
						k++;
					allign[current][k > 5 ? 5 : k]++;
					if (k == 2 && map[i][j - 1] != NONE && map[i][j + k] == NONE)
						capt[current]++;
				}
				if (i - 1 >= 0 && j - 1 >= 0 && current != map[i - 1][j - 1])
				{
					int k = 0;
					while (i + k < 19 && j + k < 19 && current == map[i + k][j + k])
						k++;
					allign[current][k > 5 ? 5 : k]++;
					if (k == 2 && map[i - 1][j - 1] != NONE && map[i + k][j + k] == NONE)
						capt[current]++;
				}
				if (i - 1 >= 0 && j + 1 < 19 && current != map[i - 1][j + 1])
				{
					int k = 0;
					while (i + k < 19 && j - k >= 0 && current == map[i + k][j - k])
						k++;
					allign[current][k > 5 ? 5 : k]++;
					if (k == 2 && map[i - 1][j + 1] != NONE && map[i + k][j - k] == NONE)
						capt[current]++;
				}
			}
		}
	}

	//count my columns lines and diagonal
	//add my capture
	//substract opponents lines columns and diagonals
	//substract opponents captures
	// if (currentColor == WHITE)
	// {
	// 	ret += nbWhiteTwoRow * TWOROW;
	// 	ret += nbWhiteThreeRow * THREEROW;
	// 	ret += nbWhiteFourRow * FOURROW;
	// 	ret += nbWhiteFiveRow * FIVEROW;
	// 	ret += nbBlackTwoRow * ENEMYTWO;
	// 	ret += nbBlackThreeRow * ENEMYTHREE;
	// 	ret += nbBlackFourRow * ENEMYFOUR;
	// 	ret += nbBlackFiveRow * ENEMYFIVE;
	// 	ret += nbCaptWhite * 50;
	// 	ret -= nbCaptBlack * 30;
	// }
	// else
	// {
		// printf("nbBlackTwoRow->%d nbBlackthreeRow->%d nbBlackfourRow->%d nbBlackfiveRow->%d nbwhiteTwoRow->%d nbwhitethreeRow->%d nbwhitefourRow->%d nbwhitefiverow->%d\n"
		// 	,nbBlackTwoRow, nbBlackThreeRow, nbBlackFourRow, nbBlackFiveRow, nbWhiteTwoRow, nbWhiteThreeRow, nbWhiteFourRow, nbWhiteFiveRow);
		ret += allign[BLACK][2] * TWOROW;
		ret += allign[BLACK][3] * THREEROW;
		ret += allign[BLACK][4] * FOURROW;
		ret += allign[BLACK][5] * FIVEROW;
		ret += allign[WHITE][2] * ENEMYTWO;
		ret += allign[WHITE][3] * ENEMYTHREE;
		ret += allign[WHITE][4] * ENEMYFOUR;
		// std::cout << "ret align : " << ret << std::endl;
		if (allign[WHITE][5])
		{
			return LOOSE;
			Finalstate = true;
		}
		if (capt[WHITE] == 1)
			ret += CAPTUREONE;
		else if (capt[WHITE] == 2)
			ret += CAPTURETWO;
		else if (capt[WHITE] == 3)
			ret += CAPTURETHREE;
		else if (capt[WHITE] == 4)
			ret += CAPTUREFOUR;
		else if (capt[WHITE] >= 5)
		{
			return WIN;
			Finalstate = true;
		}

		if (capt[BLACK] == 1)
			ret -= CAPTUREONE * 10;
		else if (capt[BLACK] == 2)
			ret -= CAPTURETWO * 10;
		else if (capt[BLACK] == 3)
			ret -= CAPTURETHREE * 10;
		else if (capt[BLACK] == 4)
			ret -= CAPTUREFOUR * 10;
		else if (capt[BLACK] >= 5)
		{
			ret = LOOSE;
			Finalstate = true;
			// std::cout << ret << std::endl;
		}
	//}
		heuristic = ret;
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

	if (nbThrees > 1)
		return false;
	return true;
}

void GameState::checkVoisin(int x, int y, eState color)
{
	(void)color;
	//verticale
	// int j = 0;
	if (y - 1 >= 0 && map[y - 1][x] == NONE)
		coups.insert(Point(x, y - 1, 0));
	// if (y - 1 >= 0 && (map[y - 1][x] == color || map[y - 1][x] == NONE))
	// {
	// 	int i = 1;
	// 	int k = 1;
	// 	while (i <= 5 && y - i >= 0 && (map[y - i][x] == color || map[y - i][x] == NONE))
	// 	{
	// 		if (map[y - i][x] == color)
	// 			k++;
	// 		i++;
	// 	}
	// 	// std::cout << "haut : " << k << std::endl;
	// 	if (y - i >= 0 && map[y - i][x] == NONE)
	// 		j = k;
	// 	if (k >= 5)
	// 	{
	// 			if (color == WHITE)
	// 			{
	// 				nbWhiteFourRow -=1;
	// 				nbWhiteFiveRow +=1;
	// 			}
	// 			else
	// 			{
	// 				nbBlackFourRow -=1;
	// 				nbBlackFiveRow +=1;
	// 			}
	// 	}
	// }
	if (y + 1 < 19 && map[y + 1][x] == NONE)
		coups.insert(Point(x, y + 1, 0));
	// if (y + 1 < 19 && (map[y + 1][x] == color || map[y + 1][x] == NONE))
	// {
	// 	int k = 0;
	// 	int i = 1;
	// 	while (i <= 5 && y + i < 19 && (map[y + i][x] == color || map[y + i][x] == NONE))
	// 	{
	// 		if (map[y + i][x] == color)
	// 			k++;
	// 		i++;
	// 	}
	// 	if (y + i < 19 && map[y + i][x] == NONE)
	// 	{
	// 	// std::cout << "bas : " << k << std::endl;
	// 		j += k;
	// 		if (j == 2)
	// 		{
	// 			if (color == WHITE)
	// 				nbWhiteTwoRow +=1;
	// 			else
	// 				nbBlackTwoRow +=1;
	// 		}
	// 		else if (j == 3)
	// 		{
	// 			if (color == WHITE)
	// 			{
	// 				nbWhiteTwoRow -= 1;
	// 				nbWhiteThreeRow +=1;
	// 			}
	// 			else
	// 			{
	// 				nbBlackTwoRow -= 1;
	// 				nbBlackThreeRow +=1;
	// 			}
	// 		}
	// 		else if (j == 4)
	// 		{
	// 			if (color == WHITE)
	// 			{
	// 				nbWhiteThreeRow -=1;
	// 				nbWhiteFourRow +=1;
	// 			}
	// 			else
	// 			{
	// 				nbBlackThreeRow -=1;
	// 				nbBlackFourRow +=1;
	// 			}
	// 		}
	// 	}
	// 	if (k >= 5)
	// 		{
	// 			if (color == WHITE)
	// 			{
	// 				nbWhiteFourRow -=1;
	// 				nbWhiteFiveRow +=1;
	// 			}
	// 			else
	// 			{
	// 				nbBlackFourRow -=1;
	// 				nbBlackFiveRow +=1;
	// 			}
	// 		}
	// }

	//back slash
	// j = 0;
	if (y - 1 >= 0 && x - 1 >= 0 && map[y - 1][x - 1] == NONE)
		coups.insert(Point(x - 1, y - 1, 0));
	// if (y - 1 >= 0 && x - 1 >= 0 && (map[y - 1][x - 1] == color || map[y - 1][x - 1] == NONE))
	// {
	// 	int k = 1;
	// 	int i = 1;
	// 	while (i <= 5 && y - i >= 0 && x - i >= 0 && (map[y - i][x - i] == color || map[y - i][x - i] == NONE))
	// 	{
	// 		if (map[y - i][x - i] == color)
	// 			k++;
	// 		i++;
	// 	}
	// 	if (y - i >= 0 && x - i >= 0 && map[y - i][x - i] == NONE)
	// 		j = k;
	// 	if (j >= 5)
	// 		{
	// 			if (color == WHITE)
	// 			{
	// 				nbWhiteFourRow -=1;
	// 				nbWhiteFiveRow +=1;
	// 			}
	// 			else
	// 			{
	// 				nbBlackFourRow -=1;
	// 				nbBlackFiveRow +=1;
	// 			}
	// 		}
	// }
	if (y + 1 < 19 && x + 1 < 19 && map[y + 1][x + 1] == NONE)
		coups.insert(Point(x + 1, y + 1, 0));
	// if (y + 1 < 19 && x + 1 < 19 && (map[y + 1][x + 1] == color || map[y + 1][x + 1] == NONE))
	// {
	// 	int k = 0;
	// 	int i = 1;
	// 	while (i <= 5 && y + i < 19 && x + i < 19 && (map[y + i][x + i] == color || map[y + i][x + i] == NONE))
	// 	{
	// 		if (map[y + i][x + i] == color)
	// 			k++;
	// 		i++;
	// 	}
	// 	if (y + i < 19 && x + i < 19 && map[y + i][x + i] == NONE)
	// 	{
	// 		j += k;
	// 		if (j == 2)
	// 		{
	// 			if (color == WHITE)
	// 				nbWhiteTwoRow +=1;
	// 			else
	// 				nbBlackTwoRow +=1;
	// 		}
	// 		else if (j == 3)
	// 		{
	// 			if (color == WHITE)
	// 			{
	// 				nbWhiteTwoRow -= 1;
	// 				nbWhiteThreeRow +=1;
	// 			}
	// 			else
	// 			{
	// 				nbBlackTwoRow -= 1;
	// 				nbBlackThreeRow +=1;
	// 			}
	// 		}
	// 		else if (j == 4)
	// 		{
	// 			if (color == WHITE)
	// 			{
	// 				nbWhiteThreeRow -=1;
	// 				nbWhiteFourRow +=1;
	// 			}
	// 			else
	// 			{
	// 				nbBlackThreeRow -=1;
	// 				nbBlackFourRow +=1;
	// 			}
	// 		}
	// 	}
	// 	if (j >= 5)
	// 		{
	// 			if (color == WHITE)
	// 			{
	// 				nbWhiteFourRow -=1;
	// 				nbWhiteFiveRow +=1;
	// 			}
	// 			else
	// 			{
	// 				nbBlackFourRow -=1;
	// 				nbBlackFiveRow +=1;
	// 			}
	// 		}
	// }

	//slash
	// j = 0;
	if (y - 1 >= 0 && x + 1 < 19 && map[y - 1][x + 1] == NONE)
		coups.insert(Point(x + 1, y - 1, 0));
	// if (y - 1 >= 0 && x + 1 < 19 && (map[y - 1][x + 1] == color || map[y - 1][x + 1] == NONE))
	// {
	// 	int i = 1;
	// 	int k = 1;
	// 	while (i <= 5 && y - i >= 0 && x + i < 19 && (map[y - i][x + i] ==color || map[y - i][x + i] == NONE))
	// 	{
	// 		if (map[y - i][x + i] ==color)
	// 			k++;
	// 		i++;
	// 	}
	// 	if (y - i >= 0 && x + i < 19 && map[y - i][x + i] == NONE)
	// 	{
	// 		j = k;
	// 	}
	// 	if (j >= 5)
	// 		{
	// 			if (color == WHITE)
	// 			{
	// 				nbWhiteFourRow -=1;
	// 				nbWhiteFiveRow +=1;
	// 			}
	// 			else
	// 			{
	// 				nbBlackFourRow -=1;
	// 				nbBlackFiveRow +=1;
	// 			}
	// 		}
	// }
	if (y + 1 < 19 && x - 1 >= 0 && map[y + 1][x - 1] == NONE)
		coups.insert(Point(x - 1, y + 1, 0));
	// if (y + 1 < 19 && x - 1 >= 0 && (map[y + 1][x - 1] == color || map[y + 1][x - 1] == NONE))
	// {
	// 	int k = 0;
	// 	int i = 1;
	// 	while (i <= 5 && y + i < 19 && x - i >= 0 && (map[y + i][x - i] == color || map[y + i][x - i] == NONE))
	// 	{
	// 		if (map[y + i][x - i] == color)
	// 			k++;
	// 		i++;
	// 	}
	// 	if (y + i < 19 && x - i >= 0 && map[y + i][x - i] == NONE)
	// 	{
	// 		j += k;
	// 		if (j == 2)
	// 		{
	// 			if (color == WHITE)
	// 				nbWhiteTwoRow +=1;
	// 			else
	// 				nbBlackTwoRow +=1;
	// 		}
	// 		else if (j == 3)
	// 		{
	// 			if (color == WHITE)
	// 			{
	// 				nbWhiteTwoRow -= 1;
	// 				nbWhiteThreeRow +=1;
	// 			}
	// 			else
	// 			{
	// 				nbBlackTwoRow -= 1;
	// 				nbBlackThreeRow +=1;
	// 			}
	// 		}
	// 		else if (j == 4)
	// 		{
	// 			if (color == WHITE)
	// 			{
	// 				nbWhiteThreeRow -=1;
	// 				nbWhiteFourRow +=1;
	// 			}
	// 			else
	// 			{
	// 				nbBlackThreeRow -=1;
	// 				nbBlackFourRow +=1;
	// 			}
	// 		}
	// 	}
	// 	if (j >= 5)
	// 		{
	// 			if (color == WHITE)
	// 			{
	// 				nbWhiteFourRow -=1;
	// 				nbWhiteFiveRow +=1;
	// 			}
	// 			else
	// 			{
	// 				nbBlackFourRow -=1;
	// 				nbBlackFiveRow +=1;
	// 			}
	// 		}
	// }

	//horizontal
	// j = 0;
	if (x + 1 < 19 && map[y][x + 1] == NONE)
		coups.insert(Point(x + 1, y, 0));
	if (x - 1 >= 0 && map[y][x - 1] == NONE)
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
				coups.insert(Point(x - i + 1, y, 0));
				coups.insert(Point(x - i + 2, y, 0));
				(color == BLACK ? nbCaptBlack : nbCaptWhite)++;
				(color == BLACK ? nbWhiteTwoRow : nbBlackTwoRow)--;
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
		else
			break;
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
				coups.insert(Point(x, y - i + 1, 0));
				coups.insert(Point(x, y - i + 2, 0));
				(color == BLACK ? nbCaptBlack : nbCaptWhite)++;
				(color == BLACK ? nbWhiteTwoRow : nbBlackTwoRow)--;
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
		else
			break;
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
				coups.insert(Point(x - i + 1, y - i + 1, 0));
				coups.insert(Point(x - i + 2, y - i + 2, 0));
				(color == BLACK ? nbCaptBlack : nbCaptWhite)++;
				(color == BLACK ? nbWhiteTwoRow : nbBlackTwoRow)--;
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
		else
			break;
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
				coups.insert(Point(x + i - 1, y, 0));
				coups.insert(Point(x + i - 2, y, 0));
				(color == BLACK ? nbCaptBlack : nbCaptWhite)++;
				(color == BLACK ? nbWhiteTwoRow : nbBlackTwoRow)--;
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
		else
			break;
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
				coups.insert(Point(x, y + i - 1, 0));
				coups.insert(Point(x, y + i - 2, 0));
				(color == BLACK ? nbCaptBlack : nbCaptWhite)++;
				(color == BLACK ? nbWhiteTwoRow : nbBlackTwoRow)--;
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
		else
			break;
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
				coups.insert(Point(x + i - 1, y + i - 1, 0));
				coups.insert(Point(x + i - 2, y + i - 2, 0));
				(color == BLACK ? nbCaptBlack : nbCaptWhite)++;
				(color == BLACK ? nbWhiteTwoRow : nbBlackTwoRow)--;
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
		else
			break;
		i++;
	}
	if (win == 5)
		throw new VictoryException(color);
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
		else
			break;
		i++;
	}
	if (win == 5)
		throw new VictoryException(color);
	capt = 0;
	win = 1;
	i = 1;
	while (x + i < 19 && y - i >= 0 && i < 5 && map[y - i][x + i] == color)
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
		else
			break;
		i++;
	}
	if (win == 5)
		throw new VictoryException(color);
}

void GameState::checkVictoireCrazy(int x, int y, eState color)
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
				coups.insert(Point(x - i + 1, y, 0));
				coups.insert(Point(x - i + 2, y, 0));
				(color == BLACK ? nbCaptBlack : nbCaptWhite)++;
				(color == BLACK ? nbWhiteTwoRow : nbBlackTwoRow)--;
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
		Finalstate = true;
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
				coups.insert(Point(x, y - i + 1, 0));
				coups.insert(Point(x, y - i + 2, 0));
				(color == BLACK ? nbCaptBlack : nbCaptWhite)++;
				(color == BLACK ? nbWhiteTwoRow : nbBlackTwoRow)--;
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
		Finalstate = true;
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
				coups.insert(Point(x - i + 1, y - i + 1, 0));
				coups.insert(Point(x - i + 2, y - i + 2, 0));
				(color == BLACK ? nbCaptBlack : nbCaptWhite)++;
				(color == BLACK ? nbWhiteTwoRow : nbBlackTwoRow)--;
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
		Finalstate = true;
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
				coups.insert(Point(x + i - 1, y, 0));
				coups.insert(Point(x + i - 2, y, 0));
				(color == BLACK ? nbCaptBlack : nbCaptWhite)++;
				(color == BLACK ? nbWhiteTwoRow : nbBlackTwoRow)--;
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
		Finalstate = true;
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
				coups.insert(Point(x, y + i - 1, 0));
				coups.insert(Point(x, y + i - 2, 0));
				(color == BLACK ? nbCaptBlack : nbCaptWhite)++;
				(color == BLACK ? nbWhiteTwoRow : nbBlackTwoRow)--;
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
		Finalstate = true;
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
				coups.insert(Point(x + i - 1, y + i - 1, 0));
				coups.insert(Point(x + i - 2, y + i - 2, 0));
				(color == BLACK ? nbCaptBlack : nbCaptWhite)++;
				(color == BLACK ? nbWhiteTwoRow : nbBlackTwoRow)--;
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
		Finalstate = true;
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
				coups.insert(Point(x - i + 1, y + i - 1, 0));
				coups.insert(Point(x - i + 2, y + i - 2, 0));
				(color == BLACK ? nbCaptBlack : nbCaptWhite)++;
				(color == BLACK ? nbWhiteTwoRow : nbBlackTwoRow)--;
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
		Finalstate = true;
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
				coups.insert(Point(x + i - 1, y - i + 1, 0));
				coups.insert(Point(x + i - 2, y - i + 2, 0));
				(color == BLACK ? nbCaptBlack : nbCaptWhite)++;
				(color == BLACK ? nbWhiteTwoRow : nbBlackTwoRow)--;
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
}

bool GameState::Play(int x, int y, eState color)
{
	if (coups.count(Point(x, y, 0)) > 0 && checkThree(x, y, color))
	{
		map[y][x] = color;
		checkVictoire(x, y, color);
		coups.erase(Point(x, y, 0));
		checkVoisin(x, y, color);
		for (auto i = coups.begin(); i != coups.end(); ++i)
		{
			if (!checkThree((*i).getX(), (*i).getY(), color))
				coups.erase(*i);
		}
		return true;
	}
	return false;
}

bool GameState::TheoricPlay(int x, int y, eState color)
{
	if (coups.count(Point(x, y, 0)) > 0 && checkThree(x, y, color))
	{
		map[y][x] = color;
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

std::vector<GameState> GameState::GenerateSons()
{
	std::vector<GameState> sons;

	auto reverse = (currentColor == WHITE ? BLACK : WHITE);
	for (auto i = coups.begin(); i != coups.end(); ++i)
	{
		if(checkThree((*i).getX(), (*i).getY(), reverse))
		{
			Input test(NOINPUT, (*i).getX(), (*i).getY());
			GameState son(*this);
			son.Update(test, reverse);
			sons.push_back(son);
		}
	}
	return sons;
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
