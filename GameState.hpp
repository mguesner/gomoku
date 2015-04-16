#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "Point.hpp"
#include "VictoryException.hpp"

enum eState
{
	NONE = 0,
	BLACK,
	WHITE
};

class GameState
{
public:
	GameState();
	GameState(GameState const & src);
	GameState& operator=(GameState const & rhs);
	void Display();
	void GameStart();
	eState **GetMap();
	bool Play(int, int, eState color);
	~GameState();
private:
	bool checkVoisin(int, int, eState);
	void checkVictoire(int, int, eState);
	eState map[19][19];
	int nbCaptBlack;
	int nbCaptWhite;
};


#endif
