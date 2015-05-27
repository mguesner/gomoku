#include "GameState.hpp"

char GameState::map[19][19] = {{NONE}};

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
}

GameState::GameState(Input test, int blackcpt, int whitecpt, char turnColor)
{
	move = test;
	nbCaptBlack = blackcpt;
	nbCaptWhite = whitecpt;
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

void	GameState::Update(Input test, char turnColor)
{
	move = test;
	currentColor = turnColor;
	DoMove();
	heuristic = Heuristic();
	Undo();
}

void	GameState::DoMove()
{
	//update table and list of possible move

}

void GameState::Undo()
{
	//remove move and clear possible moves

}

//HEURISTIC FUNCTION RETURN MAX VALUE EVALUATING CURRENT PLAYER POSITION

int		GameState::Heuristic()
{
	return std::rand();
}

void GameState::GameStart()
{
	map[9][9] = BLACK;
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

	(void)ret;
	(void)maximizerColor;
}

bool GameState::Play(int x, int y, char color)
{
	//try to play at x, y using color
	//return false if forbidden



	// check if move is valide using list of possible
	// DoMove
	// Update heuristic
	move = Input(MOUSE ,x, y);
	DoMove();
	heuristic = Heuristic();
	(void)x;
	(void)y;
	(void)color;
	return true;
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
			std::cout << (map[i][j] == NONE ? "+" : (map[i][j] == BLACK ? "N" : "B"));
		}
		std::cout << std::endl;
	}
}
