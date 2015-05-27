#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "Gomoku.hpp"
#include "Point.hpp"
#include "VictoryException.hpp"
#include "Input.hpp"

#define TWOROWONEWAY 11
#define TWOROWTWOWAY 31
#define THREEROWONEWAY 21
#define THREEROWTWOWAY 201
#define FOURROWONEWAY 101
#define FOURROWTWOWAY 100000
#define ENEMYTWOONEWAY -10
#define ENEMYTWOTWOWAY -30
#define ENEMYTHREEONEWAY -20
#define ENEMYTHREETWOWAY -150
#define ENEMYFOUR -200
#define CAPTUREONE 300
#define CAPTURETWO 600
#define CAPTURETHREE 10000
#define CAPTUREFOUR 50000
#define LOOSE -1000000000
#define WIN 1000000000


class GameState
{
public:
	GameState(); //empty constructor == root map
	GameState(Input test, int blackcpt, int whitecpt, char); //constructeur pour generer les fils
	GameState(GameState const & src);
	GameState& operator=(GameState const & rhs);
	bool	operator<(GameState const & src) const;
	bool	operator==(GameState const & src) const;
	bool	operator<=(GameState const & src) const;
	bool	operator>(GameState const & src) const;
	bool	operator>=(GameState const & src) const;
	void	Update(Input test, char turnColor);
	void Display() const;
	void DoMove();
	void GameStart();
	void Info();
	void Undo();
	int Heuristic();
	void GenerateSons(std::vector<GameState>&);
	int GetHeuristic();
	Input GetMove();
	bool Play(int x, int y, char color);
	int GetCapture(char);
	void SetColor(char color);

	std::vector<GameState> successors;

	char *GetMap();
	bool IsFinalState() const;
	~GameState();
	static char map[19][19];
private:
	int nbWhiteTwoRow;
	int nbWhiteThreeRow;
	int nbWhiteFourRow;
	int nbWhiteFiveRow;
	int nbBlackTwoRow;
	int nbBlackThreeRow;
	int nbBlackFourRow;
	int nbBlackFiveRow;
	int nbCaptBlack;
	int nbCaptWhite;
	bool Finalstate;
	char maximizerColor;
	char currentColor;
	int heuristic;
	Input move;
};


#endif
