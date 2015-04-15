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
	bool Play(int, int, eState color);
	~GameState();
private:
	void checkCapture(int, int, eState);
	bool checkVoisin(int, int);
	void checkVictoire(int, int, eState);
	eState map[19][19];
};


#endif
