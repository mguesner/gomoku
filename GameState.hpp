#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <queue>
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
#define POTENTIALCAPTURE 100
#define CAPTUREONE 300
#define CAPTURETWO 600
#define CAPTURETHREE 10000
#define CAPTUREFOUR 50000
#define WIN 100000000


class GameState
{
public:
	GameState(); //empty constructor == root map
	GameState(Input test, char); //constructeur pour generer les fils
	GameState(GameState const & src);
	GameState& operator=(GameState const & rhs);
	bool	operator<(GameState const & src) const;
	bool	operator==(GameState const & src) const;
	bool	operator<=(GameState const & src) const;
	bool	operator>(GameState const & src) const;
	bool	operator>=(GameState const & src) const;
	bool	Update(Input test, char turnColor);
	void Display() const;
	bool DoMove();
	void DoManualMove();
	void GameStart();
	void Info();
	void Undo();
	void ManualUndo(int, int);
	bool CaptureAndCount(int, int);
	void Capture(int, int, int ,int);
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
	static int	playableMove[19][19];
private:
	int	nbCapture;
	std::pair<Point, Point> capture[8];
	char		align[2][2][5];
	int nbCaptBlack;
	int nbCaptWhite;
	bool Finalstate;
	char maximizerColor;
	char currentColor;
	int heuristic;
	Input move;
};


#endif
