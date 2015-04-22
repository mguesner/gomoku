#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "Gomoku.hpp"
#include "Point.hpp"
#include "VictoryException.hpp"
#include "Input.hpp"

#define TWOROW 20
#define THREEROW 40
#define FOURROW 70
#define FIVEROW 4000
#define ENEMYTWO -19
#define ENEMYTHREE -39
#define ENEMYFOUR -71
#define ENEMYFIVE -4500
#define CAPTUREONE 40
#define CAPTURETWO 70
#define CAPTURETHREE 90
#define CAPTUREFOUR 200
#define CAPTUREFIVE 10000

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
	GameState(eState real[19][19], Input test, int blackcpt, int whitecpt, eState); //constructeur pour generer les fils
	GameState(GameState const & src);
	GameState& operator=(GameState const & rhs);
	bool	operator<(GameState const & src) const;
	bool	operator==(GameState const & src) const;
	bool	operator<=(GameState const & src) const;
	bool	operator>(GameState const & src) const;
	bool	operator>=(GameState const & src) const;
	void	Update(Input test, eState turnColor);
	void Display();
	void GameStart();
	void Info();

	std::vector<GameState> GenerateSons();
	int GetHeuristic();
	Input GetMove();
	int BrainDead() const;
	void SetColor(eState color);

	eState *GetMap();
	bool TheoricPlay(int, int, eState color);
	bool Play(int, int, eState color);
	bool CheckMove(int, int, eState color);
	~GameState();
private:
	void checkVoisin(int, int, eState);
	void checkVictoire(int, int, eState);
	bool checkThree(int, int, eState);
	std::set<Point> coups;
	eState map[19][19];
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
	eState currentColor;
	int heuristic;
	Input move;
};


#endif
