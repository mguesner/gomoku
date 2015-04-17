#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "Gomoku.hpp"
#include "Point.hpp"
#include "VictoryException.hpp"
#include "Input.hpp"

enum eState
{
	NONE = 0,
	BLACK,
	WHITE
};

class GameState
{
public:
	GameState(); //empty constructor == root map
	GameState(eState real[19][19], Input test, int blackcpt, int whitecpt); //constructeur pour generer les fils
	GameState(GameState const & src);
	GameState& operator=(GameState const & rhs);
	void Display();
	void GameStart();

	std::vector<GameState*> GenerateSons();
	int GetHeuristic();
	Input GetMove();

	eState *GetMap();
	bool Play(int, int, eState color);
	bool CheckMove(int, int, eState color);
	~GameState();
private:
	bool checkVoisin(int, int, eState);
	void checkVictoire(int, int, eState);
	eState map[19][19];
	int nbCaptBlack;
	int nbCaptWhite;
	int heuristic;
	Input move;
};


#endif
