#include "GameState.hpp"

char GameState::map[19][19] = {{NONE}};
int GameState::playableMove[19][19] = {{0}};

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
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			map[j][i] = NONE;
		}
	}
	Finalstate = false;
}

GameState::GameState(Input test, char turnColor)
{
	move = test;
	currentColor = turnColor;
}

GameState::GameState(GameState const & src)
{
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

//change to bool return
bool	GameState::DoMove()
{
	//update table
	//
	int y = move.GetY();
	int x = move.GetX();
	map[y][x] = currentColor;

	// list of possible move update
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

	//capture and update alignment
	return CaptureAndCount(x, y);


}

//change to bool return
bool	GameState::DoMove(char color)
{
	//update table
	//
	int y = move.GetY();
	int x = move.GetX();
	map[y][x] = color;


	//list of possible move update
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

	//capture and update alignment
	// if this move add 2 three == forbidden
	return CaptureAndCount(x, y);



}

bool GameState::CaptureAndCount(int x, int y)
{
	int min_x = (x - 5 >= 0) ? x - 5 : 0;
	int min_y = (y - 5 >= 0) ? y - 5 : 0;
	int max_x = (x + 5 < 19) ? x + 5 : 18;
	int max_y = (y + 5 < 19) ? y + 5 : 18;

	bool iAmBlack = currentColor == BLACK ? true : false;
	int j = min_x;
	int i = min_y;
	while (i <= max_y && j <= max_x)
	{

		j++;
		i++;
	}

	j = max_y;
	for (int i = min_x; i <= max_x && j >= min_y; i++)
	{

		j--;
	}

	int openSet = -1;
	int counter = 0;
	for (int i = min_y; i <= max_y; i++)
	{
		if (map[i][x] == currentColor)
		{
			if (openSet == -1)
				openSet = 1;
			else
				openSet++;
		}
		else if (map[i][x] != NONE)
			;
		counter++;

	}

	for(int i = min_x; i <= max_x; i++)
	{
		;
	}
	//return false if 2 trhee are adds
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

}

void GameState::ManualUndo(int x, int y)
{

}

//HEURISTIC FUNCTION RETURN MAX VALUE EVALUATING CURRENT PLAYER POSITION

int		GameState::Heuristic()
{
	// maj des variables alignement capture
	return std::rand();
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
		DoMove(color);
		heuristic = Heuristic();
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
