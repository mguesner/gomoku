#include "GameState.hpp"

char GameState::map[19][19] = {{NONE}};
int GameState::playableMove[19][19] = {{0}};

GameState::GameState()
{
	nbCaptWhite = 0;
	nbCaptBlack = 0;
	nbCapture = 0;
	std::memset(align, 0, 20);
	std::memset(map, NONE, 19 * 19);
	Finalstate = false;
}

GameState::GameState(Input test, char turnColor)
{
	move = test;
	currentColor = turnColor;
}

GameState::GameState(GameState const & src)
{
	nbCapture = 0;
	std::memset(capture, 0, 8 * sizeof(std::pair<Point, Point>));
	nbCaptBlack = src.nbCaptBlack;
	nbCaptWhite = src.nbCaptWhite;
	currentColor = src.currentColor;
	heuristic = src.heuristic;
	move = src.move;
	Finalstate = src.Finalstate;
	std::memcpy(align, src.align, 20);
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


//change to bool return
bool	GameState::Update(Input test, char turnColor)
{
	move = test;
	currentColor = turnColor;
	bool ret = DoMove();
	heuristic = Heuristic();
	Undo();
	return ret;
}

void	GameState::DoManualMove()
{
	int y = move.GetY();
	int x = move.GetX();
	map[y][x] = currentColor;
	if (y - 1 >= 0 && x - 1 >= 0)
		(playableMove[y - 1][x -1])++;
	if (y + 1 < 19 && x + 1 < 19)
		(playableMove[y + 1][x + 1])++;
	if (y - 1 >= 0 && x + 1 < 19)
		(playableMove[y - 1][x + 1])++;
	if (y + 1 < 19 && x - 1 >= 0)
		(playableMove[y + 1][x - 1])++;
	if (y + 1 < 19)
		(playableMove[y + 1][x])++;
	if (x + 1 < 19)
		(playableMove[y][x + 1])++;
	if (y - 1 >= 0)
		(playableMove[y - 1][x])++;
	if (x - 1 >= 0)
		(playableMove[y][x - 1])++;
}

//change to bool return
bool	GameState::DoMove()
{
	//update table
	//
	nbCapture = 0;
	int y = move.GetY();
	int x = move.GetX();
	//capture and update alignment
	map[y][x] = currentColor;//list of possible move update
	if (y - 1 >= 0 && x - 1 >= 0)
		(playableMove[y - 1][x -1])++;
	if (y + 1 < 19 && x + 1 < 19)
		(playableMove[y + 1][x + 1])++;

	if (y - 1 >= 0 && x + 1 < 19)
		(playableMove[y - 1][x + 1])++;
	if (y + 1 < 19 && x - 1 >= 0)
		(playableMove[y + 1][x - 1])++;
	if (y + 1 < 19)
		(playableMove[y + 1][x])++;
		if (x + 1 < 19)
			(playableMove[y][x + 1])++;
		if (y - 1 >= 0)
			(playableMove[y - 1][x])++;
		if (x - 1 >= 0)
			(playableMove[y][x - 1])++;
	if (CaptureAndCount(x, y))
	{
		return true;
	}
	return false;


}

void GameState::Capture(int x1, int y1, int x2, int y2)
{
	// std::cout << "capture" << std::endl;
	if (currentColor == BLACK)
		nbCaptBlack++;
	else
		nbCaptWhite++;
	map[y1][x1] = NONE;
	if (y1 - 1 >= 0 && x1 - 1 >= 0)
		(playableMove[y1 - 1][x1 -1])--;
	if (y1 + 1 < 19 && x1 + 1 < 19)
		(playableMove[y1 + 1][x1 + 1])--;


	if (y1 - 1 >= 0 && x1 + 1 < 19)
		(playableMove[y1 - 1][x1 + 1])--;
	if (y1 + 1 < 19 && x1 - 1 >= 0)
		(playableMove[y1 + 1][x1 - 1])--;

	if (y1 + 1 < 19)
		(playableMove[y1 + 1][x1])--;
	if (x1 + 1 < 19)
		(playableMove[y1][x1 + 1])--;
	if (y1 - 1 >= 0)
		(playableMove[y1 - 1][x1])--;
	if (x1 - 1 >= 0)
		(playableMove[y1][x1 - 1])--;
	map[y2][x2] = NONE;
	if (y2 - 1 >= 0 && x2 - 1 >= 0)
		(playableMove[y2 - 1][x2 -1])--;
	if (y2 + 1 < 19 && x2 + 1 < 19)
		(playableMove[y2 + 1][x2 + 1])--;


	if (y2 - 1 >= 0 && x2 + 1 < 19)
		(playableMove[y2 - 1][x2 + 1])--;
	if (y2 + 1 < 19 && x2 - 1 >= 0)
		(playableMove[y2 + 1][x2 - 1])--;

	if (y2 + 1 < 19)
		(playableMove[y2 + 1][x2])--;
	if (x2 + 1 < 19)
		(playableMove[y2][x2 + 1])--;
	if (y2 - 1 >= 0)
		(playableMove[y2 - 1][x2])--;
	if (x2 - 1 >= 0)
		(playableMove[y2][x2 - 1])--;
	capture[nbCapture] = std::pair<Point, Point>(Point(x1, y1, 0), Point(x2, y2, 0));
	nbCapture++;
}

bool GameState::CaptureAndCount(int x, int y)
{
	int min_x = (x - 5 >= 0) ? x - 5 : 0;
	int min_y = (y - 5 >= 0) ? y - 5 : 0;
	int max_x = (x + 5 < 19) ? x + 5 : 18;
	int max_y = (y + 5 < 19) ? y + 5 : 18;

	int right_y = y + 1;
	int right_x = x + 1;
	int	lastNbThree = align[0][currentColor == WHITE ? 0 : 1][2];
	bool alignement = true;
	int num = 0;

	if (right_y <= max_y && right_x <= max_x && map[right_y][right_x] == currentColor)
		; //on est en mode alignement
	else if (right_y <= max_y && right_x <= max_x && map[right_y][right_x] != NONE)
		alignement = false;// mode capture ou blocage
	int ennemy = 0;
	int total = 0;
	bool capture = false;
	bool lock = false;
	while (right_y <= max_y && right_x <= max_x)
	{
		if (alignement)
		{
			if (map[right_y][right_x] == currentColor)
				num++;
			else if (map[right_y][right_x] != NONE)
			{
				lock = true;
				break;
			}
		}
		else
		{
			if (map[right_y][right_x] == currentColor)
			{
				if (ennemy == 2 && total == 2)
				{
					capture = true;
					Capture(right_x - 1, right_y - 1, right_x - 2, right_y - 2);
					//CAPTURE HERE
				}
				lock = true;
				break;
			}
			else if (map[right_y][right_x] != NONE)
				ennemy++;
		}
		total++;
		right_x++;
		right_y++;
	}
	if (!alignement && ennemy > 1)
	{
		align[lock][currentColor == WHITE ? 1 : 0][ennemy - 1]--;
		if (!lock)
			align[!lock][currentColor == WHITE ? 1 : 0][ennemy - 1]++;
	}

	#ifdef DEBUG
	std::cout << "bas droite diag enemy = " << ennemy << " capture = " << capture << " align : " << num <<std::endl;
	#endif

	int left_y = y - 1;
	int left_x = x - 1;
	alignement = true;
	if (left_y <= max_y && left_x <= max_x && map[left_y][left_x] == currentColor)
		; //on est en mode alignement
	else if (left_y >= min_y && left_x >= min_x && map[left_y][left_x] != NONE)
		alignement = false;// mode capture ou blocage
	total = 0;
	ennemy = 0;
	capture = false;
	while (left_y >= min_y && left_x >= min_x)
	{
		if (alignement)
		{
			if (map[left_y][left_x] == currentColor)
				num++;
			else if (map[left_y][left_x] != NONE)
			{
				lock = true;
				break;
			}
		}
		else
		{
			if (map[left_y][left_x] == currentColor)
			{
				if (ennemy == 2 && total == 2)
				{
					capture = true;
					Capture(left_x + 1, left_y + 1, left_x + 2, left_y + 2);
				}
					//CAPTURE HERE
				lock = true;
				break;
			}
			else if (map[left_y][left_x] != NONE)
				ennemy++;
		}
		total++;
		left_x--;
		left_y--;
	}
	if (!alignement && ennemy > 1)
	{
		align[lock][currentColor == WHITE ? 1 : 0][ennemy - 1]--;
		if (!lock)
			align[!lock][currentColor == WHITE ? 1 : 0][ennemy - 1]++;
	}
	if (num >= 0 && num < 5)
	{
		align[lock][currentColor == WHITE ? 0 : 1][num]++;
		if (num > 0)
			align[lock][currentColor == WHITE ? 0 : 1][num - 1]--;
	}

	#ifdef DEBUG
	std::cout << "haut gauche diag enemy = " << ennemy << " capture = " << capture << " align : " << num <<std::endl;
	#endif




	//first diag analyse



	left_y = y + 1;
	left_x = x - 1;
	alignement = true;
	if (left_y <= max_y && left_x >= min_x && map[left_y][left_x] == currentColor)
		; //on est en mode alignement
	else if (left_y <= max_y && left_x >= min_x && map[left_y][left_x] != NONE)
		alignement = false;// mode capture ou blocage
	total = 0;
	ennemy = 0;
	capture = false;
	num = 0;
	while (left_y <= max_y && left_x >= min_x)
	{
		if (alignement)
		{
			if (map[left_y][left_x] == currentColor)
				num++;
			else if (map[left_y][left_x] != NONE)
			{
				lock = true;
				break;
			}
		}
		else
		{
			if (map[left_y][left_x] == currentColor)
			{
				if (ennemy == 2 && total == 2)
				{
					Capture(left_x + 1, left_y - 1, left_x + 2, left_y - 2);
					capture = true;
				}
				lock = true;
				break;
			}
			else if (map[left_y][left_x] != NONE)
				ennemy++;
		}
		total++;
		left_x--;
		left_y++;
	}
	if (!alignement && ennemy > 1)
	{
		align[lock][currentColor == WHITE ? 1 : 0][ennemy - 1]--;
		if (!lock)
			align[!lock][currentColor == WHITE ? 1 : 0][ennemy - 1]++;
	}

	#ifdef DEBUG
	std::cout << "bas gauche diag enemy = " << ennemy << " capture = " << capture << " align = " << num <<std::endl;
	#endif

	right_x = x + 1;
	right_y = y - 1;
	alignement = true;
	if (right_y <= max_y && right_x <= max_x && map[right_y][right_x] == currentColor)
		; //on est en mode alignement
	else if (right_y >= min_y && right_x >= min_x && map[right_y][right_x] != NONE)
		alignement = false;// mode capture ou blocage
	total = 0;
	ennemy = 0;
	capture = false;
	while (right_y >= min_y && right_x <= max_x)
	{
		if (alignement)
		{
			if (map[right_y][right_x] == currentColor)
				num++;
			else if (map[right_y][right_x] != NONE)
			{
				lock = true;
				break;
			}
		}
		else
		{
			if (map[right_y][right_x] == currentColor)
			{
				if (ennemy == 2 && total == 2)
				{
					Capture(right_x - 1, right_y + 1, right_x - 2, right_y + 2);
					capture = true;
				}
				lock = true;
				break;
			}
			else if (map[right_y][right_x] != NONE)
				ennemy++;
		}
		total++;
		right_x++;
		right_y--;
	}
	if (!alignement && ennemy > 1)
	{
		align[lock][currentColor == WHITE ? 1 : 0][ennemy - 1]--;
		if (!lock)
			align[!lock][currentColor == WHITE ? 1 : 0][ennemy - 1]++;
	}
	if (num >= 0 && num < 5)
	{
		align[lock][currentColor == WHITE ? 0 : 1][num]++;
		if (num > 0)
			align[lock][currentColor == WHITE ? 0 : 1][num - 1]--;
	}

	#ifdef DEBUG
	std::cout << "haut droite diag enemy = " << ennemy << " capture = " << capture << " align = " << num <<std::endl;
	#endif

	right_x = x + 1;
	alignement = true;
	if (right_x <= max_x && map[y][right_x] == currentColor)
		; //on est en mode alignement
	else if (right_x <= max_x && map[y][right_x] != NONE)
		alignement = false;// mode capture ou blocage
	num = 0;
	total = 0;
	ennemy = 0;
	capture = false;
	for (int i = right_x; i <= max_x; i++)
	{
		if (alignement)
		{
			if (map[y][i] == currentColor)
				num++;
			else if (map[y][i] != NONE)
			{
				lock = true;
				break;
			}
		}
		else
		{
			if (map[y][i] == currentColor)
			{
				if (ennemy == 2 && total == 2)
				{
					Capture(i - 1, y, i - 2, y);
					capture = true;
				}
				lock = true;
				break;
			}
			else if (map[y][i] != NONE)
				ennemy++;
		}
		total++;
	}
	if (!alignement && ennemy > 1)
	{
		align[lock][currentColor == WHITE ? 1 : 0][ennemy - 1]--;
		if (!lock)
			align[!lock][currentColor == WHITE ? 1 : 0][ennemy - 1]++;
	}

	#ifdef DEBUG
	std::cout << "droite enemy = " << ennemy << " capture = " << capture << " align = " << num <<std::endl;
	#endif

	right_x = x - 1;
	alignement = true;
	if (right_x <= max_x && map[y][right_x] == currentColor)
		; //on est en mode alignement
	else if (right_x >= min_x && map[y][right_x] != NONE)
		alignement = false;// mode capture ou blocage
	total = 0;
	ennemy = 0;
	capture = false;
	for (int i = right_x; i >= min_x; i--)
	{
		if (alignement)
		{
			if (map[y][i] == currentColor)
				num++;
			else if (map[y][i] != NONE)
			{
				lock = true;
				break;
			}
		}
		else
		{
			if (map[y][i] == currentColor)
			{
				if (ennemy == 2 && total == 2)
				{
					Capture(i + 1, y, i + 2, y);
					capture = true;
				}
				lock = true;
				break;
			}
			else if (map[y][i] != NONE)
				ennemy++;
		}
		total++;
	}
	if (!alignement && ennemy > 1)
	{
		align[lock][currentColor == WHITE ? 1 : 0][ennemy - 1]--;
		if (!lock)
			align[!lock][currentColor == WHITE ? 1 : 0][ennemy - 1]++;
	}
	if (num >= 0 && num < 5)
	{
		align[lock][currentColor == WHITE ? 0 : 1][num]++;
		if (num > 0)
			align[lock][currentColor == WHITE ? 0 : 1][num - 1]--;
	}

	#ifdef DEBUG
	std::cout << "gauche enemy = " << ennemy << " capture = " << capture << " align = " << num <<std::endl;
	#endif

	right_y = y + 1;
	alignement = true;
	if (right_y <= max_y && map[right_y][x] == currentColor)
		; //on est en mode alignement
	else if (right_y <= max_y && map[right_y][x] != NONE)
		alignement = false;// mode capture ou blocage
	num = 0;
	total = 0;
	ennemy = 0;
	capture = false;
	for(int i = right_y; i <= max_y; i++)
	{
		if (alignement)
		{
			if (map[i][x] == currentColor)
				num++;
			else if (map[i][x] != NONE)
			{
				lock = true;
				break;
			}
		}
		else
		{
			if (map[i][x] == currentColor)
			{
				if (ennemy == 2 && total == 2)
				{
					Capture(x, i - 1, x, i - 2);
					capture = true;
				}
				lock = true;
				break;
			}
			else if (map[i][x] != NONE)
				ennemy++;
		}
		total++;
	}
	if (!alignement && ennemy > 1)
	{
		align[lock][currentColor == WHITE ? 1 : 0][ennemy - 1]--;
		if (!lock)
			align[!lock][currentColor == WHITE ? 1 : 0][ennemy - 1]++;
	}

	#ifdef DEBUG
	std::cout << "bas enemy = " << ennemy << " capture = " << capture << " align = " << num <<std::endl;
	#endif

	right_y = y - 1;
	alignement = true;
	if (right_y >= min_y && map[right_y][x] == currentColor)
		; //on est en mode alignement
	else if (right_y >= min_y && map[right_y][x] != NONE)
		alignement = false;// mode capture ou blocage
	total = 0;
	ennemy = 0;
	capture = false;
	for(int i = right_y; i >= min_y; i--)
	{
		if (alignement)
		{
			if (map[i][x] == currentColor)
				num++;
			else if (map[i][x] != NONE)
			{
				lock = true;
				break;
			}
		}
		else
		{
			if (map[i][x] == currentColor)
			{
				if (ennemy == 2 && total == 2)
				{
					Capture(x, i + 1, x, i + 2);
					capture = true;
				}
				lock = true;
				break;
			}
			else if (map[i][x] != NONE)
				ennemy++;
		}
		total++;
	}
	if (!alignement && ennemy > 1)
	{
		align[lock][currentColor == WHITE ? 1 : 0][ennemy - 1]--;
		if (!lock)
			align[!lock][currentColor == WHITE ? 1 : 0][ennemy - 1]++;
	}
	if (num >= 0 && num < 5)
	{
		align[lock][currentColor == WHITE ? 0 : 1][num]++;
		if (num > 0)
			align[lock][currentColor == WHITE ? 0 : 1][num - 1]--;
	}

	#ifdef DEBUG
	std::cout << "haut enemy = " << ennemy << " capture = " << capture << " align = " << num <<std::endl;
	#endif
	//return false if 2 trhee are adds
	#ifdef DEBUG
	std::cout << "align :\tblanc :\t2 ->\tone way : " << (int)align[1][0][1] << "\n\t\t\ttwo way : " << (int)align[0][0][1]
	<< "\n\t\t3 ->\tone way : " << (int)align[1][0][2] << "\n\t\t\ttwo way : " << (int)align[0][0][2]
	<< "\n\t\t4 ->\tone way : " << (int)align[1][0][3] << "\n\t\t\ttwo way : " << (int)align[0][0][3]
	<< "\n\t\t5 ->\tone way : " << (int)align[1][0][4] << "\n\t\t\ttwo way : " << (int)align[0][0][4]
	<< "\n\tblack :\t2 ->\tone way : " << (int)align[1][1][1] << "\n\t\t\ttwo way : " << (int)align[0][1][1]
	<< "\n\t\t3 ->\tone way : " << (int)align[1][1][2] << "\n\t\t\ttwo way : " << (int)align[0][1][2]
	<< "\n\t\t4 ->\tone way : " << (int)align[1][1][3] << "\n\t\t\ttwo way : " << (int)align[0][1][3]
	<< "\n\t\t5 ->\tone way : " << (int)align[1][1][4] << "\n\t\t\ttwo way : " << (int)align[0][1][4] <<std::endl;
	#endif
	if (lastNbThree + 2 <= align[0][currentColor == WHITE ? 0 : 1][2])
		return false;
	return true;
}


void GameState::Undo()
{
	//remove move
	int y = move.GetY();
	int x = move.GetX();

	map[y][x] = NONE;

	//clear possible moves update
	if (y - 1 >= 0 && x - 1 >= 0)
		(playableMove[y - 1][x -1])--;
	if (y + 1 < 19 && x + 1 < 19)
		(playableMove[y + 1][x + 1])--;


	if (y - 1 >= 0 && x + 1 < 19)
		(playableMove[y - 1][x + 1])--;
	if (y + 1 < 19 && x - 1 >= 0)
		(playableMove[y + 1][x - 1])--;

	if (y + 1 < 19)
		(playableMove[y + 1][x])--;
	if (x + 1 < 19)
		(playableMove[y][x + 1])--;
	if (y - 1 >= 0)
		(playableMove[y - 1][x])--;
	if (x - 1 >= 0)
		(playableMove[y][x - 1])--;
	// repop les captures
	// int i = nbCapture;
	while (nbCapture)
	{
		nbCapture--;
		Point tmp = std::get<0>(capture[nbCapture]);
		int x = (int)tmp.getX();
		int y = (int)tmp.getY();
		map[y][x] = currentColor == WHITE ? BLACK : WHITE;
		if (y - 1 >= 0 && x - 1 >= 0)
			(playableMove[y - 1][x -1])++;
		if (y + 1 < 19 && x + 1 < 19)
			(playableMove[y + 1][x + 1])++;
		if (y - 1 >= 0 && x + 1 < 19)
			(playableMove[y - 1][x + 1])++;
		if (y + 1 < 19 && x - 1 >= 0)
			(playableMove[y + 1][x - 1])++;
		if (y + 1 < 19)
			(playableMove[y + 1][x])++;
		if (x + 1 < 19)
			(playableMove[y][x + 1])++;
		if (y - 1 >= 0)
			(playableMove[y - 1][x])++;
		if (x - 1 >= 0)
			(playableMove[y][x - 1])++;
		tmp = std::get<1>(capture[nbCapture]);
		x = (int)tmp.getX();
		y = (int)tmp.getY();
		map[y][x] = currentColor == WHITE ? BLACK : WHITE;
		if (y - 1 >= 0 && x - 1 >= 0)
			(playableMove[y - 1][x -1])++;
		if (y + 1 < 19 && x + 1 < 19)
			(playableMove[y + 1][x + 1])++;
		if (y - 1 >= 0 && x + 1 < 19)
			(playableMove[y - 1][x + 1])++;
		if (y + 1 < 19 && x - 1 >= 0)
			(playableMove[y + 1][x - 1])++;
		if (y + 1 < 19)
			(playableMove[y + 1][x])++;
		if (x + 1 < 19)
			(playableMove[y][x + 1])++;
		if (y - 1 >= 0)
			(playableMove[y - 1][x])++;
		if (x - 1 >= 0)
			(playableMove[y][x - 1])++;
	}

}

void GameState::ManualUndo(int x, int y)
{
	(void)x;
	(void)y;
}

//HEURISTIC FUNCTION RETURN MAX VALUE EVALUATING CURRENT PLAYER POSITION

int		GameState::Heuristic()
{
	int ret = align[1][1][1] * TWOROWONEWAY + align[1][1][2] * THREEROWONEWAY
	+ align[1][1][3] * FOURROWONEWAY + align[1][1][4] * WIN + align[0][1][1] * TWOROWTWOWAY
	+ align[0][1][2] * THREEROWTWOWAY + align[0][1][3] * FOURROWTWOWAY + align[0][1][4] * WIN
	+ nbCaptBlack * CAPTUREONE + align[1][0][1] * POTENTIALCAPTURE;
	if (ret > WIN)
	{
		Finalstate = true;
		return WIN;
	}
	int ret2 = -(align[1][0][1] * TWOROWONEWAY + align[1][0][2] * THREEROWONEWAY
		+ align[1][0][3] * FOURROWONEWAY + align[1][0][4] * WIN + align[0][0][1] * TWOROWTWOWAY
		+ align[0][0][2] * THREEROWTWOWAY + align[0][0][3] * FOURROWTWOWAY + align[0][0][4] * WIN
		+ nbCaptWhite * CAPTUREONE + align[1][1][1] * POTENTIALCAPTURE);
	if (ret2 < -WIN)
	{
		// std::cout << "heuristic : " << ret << std::endl;
		Finalstate = true;
		return -WIN;
	}
	// std::cout << "heuristic : " << ret << std::endl;
	return ret + ret2;
}

void GameState::GameStart()
{
	map[9][9] = BLACK;
	int x = 9;
	int y = 9;
	(playableMove[y - 1][x -1])++;
	(playableMove[y + 1][x + 1])++;
	(playableMove[y - 1][x + 1])++;
	(playableMove[y + 1][x - 1])++;
	(playableMove[y + 1][x])++;
	(playableMove[y][x + 1])++;
	(playableMove[y - 1][x])++;
	(playableMove[y][x - 1])++;
}



char *GameState::GetMap()
{
	return (char *)(map);
}

GameState& GameState::operator=(GameState const & src)
{
	nbCaptBlack = src.nbCaptBlack;
	nbCaptWhite = src.nbCaptWhite;
	currentColor = src.currentColor;
	heuristic = src.heuristic;
	move = src.move;
	return *this;
}

void GameState::GenerateSons(std::vector<GameState>& ret)
{
	//for each possible move
	//copy actual state
	// add color and move
	// DoMove evaluate undo
	// Update method does it
	// add this son to ret vector
	for (int x = 0; x < 19; x++)
	{
		for (int y = 0; y < 19; y++)
		{
			if (map[y][x] == NONE && playableMove[y][x])
			{
				Input test(MOUSE, x, y);
				GameState son(*this);
				char opposite = (currentColor == BLACK) ? WHITE : BLACK;
				if (son.Update(test, opposite))
					ret.push_back(son);
			}
		}
	}
	(void)maximizerColor;
}

bool GameState::Play(int x, int y, char color)
{
	//try to play at x, y using color
	//return false if forbidden



	if (x >= 0 && y >= 0 && y < 19 && x < 19
		&& map[y][x] == NONE && playableMove[y][x])
	{
		move = Input(MOUSE ,x, y);
		//if domove is true
		currentColor = color;
		if (!DoMove())
			return false;
		#ifdef DEBUG
		heuristic = Heuristic();
		#endif
		return true;
	}
	return false;
}

int GameState::GetHeuristic()
{
	return heuristic;
}

Input GameState::GetMove()
{
	return move;
}

void GameState::SetColor(char color)
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

int GameState::GetCapture(char color)
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
			std::cout << map[i][j];
		}
		std::cout << std::endl;
	}
}
