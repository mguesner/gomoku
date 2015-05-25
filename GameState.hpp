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
	GameState(eState **firstTrue); //empty constructor == root map
	GameState(eState **real, Input test, int blackcpt, int whitecpt, eState); //constructeur pour generer les fils
	GameState(GameState const & src);
	GameState& operator=(GameState const & rhs);
	bool	operator<(GameState const & src) const;
	bool	operator==(GameState const & src) const;
	bool	operator<=(GameState const & src) const;
	bool	operator>(GameState const & src) const;
	bool	operator>=(GameState const & src) const;
	void	Update(Input test, eState turnColor);
	void Display() const;
	void GameStart();
	void Info();
	void Undo();

	std::vector<GameState> GenerateSons();
	int GetHeuristic();
	Input GetMove();
	int BrainDead();
	int GetCapture(eState);
	void SetColor(eState color);

	std::vector<GameState> successors;

	eState *GetMap();
	std::set<Point> GetCoups();
	bool TheoricPlay(int, int, eState color);
	bool Play(int, int, eState color);
	bool CheckMove(int, int, eState color);
	bool IsFinalState() const;
	~GameState();
private:
	GameState();
	void checkVoisin(int, int, eState);
	void checkVictoire(int, int, eState);
	void checkVictoireCrazy(int x, int y, eState color);
	bool checkThree(int, int, eState);
	bool isCapturable(bool *check, int x, int y, eState color);
	std::set<Point> coups;
	eState **map;
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
	eState currentColor;
	int heuristic;
	Input move;
};


#endif
