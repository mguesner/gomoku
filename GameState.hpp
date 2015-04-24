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
#define ENEMYFOUR -400
#define ENEMYFIVE -100000
#define CAPTUREONE 55
#define CAPTURETWO 70
#define CAPTURETHREE 90
#define CAPTUREFOUR 200
#define CAPTUREFIVE 10000


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
	void Display() const;
	void GameStart();
	void Info();

	std::vector<GameState> GenerateSons();
	int GetHeuristic();
	Input GetMove();
	int BrainDead();
	void SetColor(eState color);

	eState *GetMap();
	std::set<Point> GetCoups();
	bool TheoricPlay(int, int, eState color);
	bool Play(int, int, eState color);
	bool CheckMove(int, int, eState color);
	bool IsFinalState() const;
	~GameState();
private:
	void checkVoisin(int, int, eState);
	void checkVictoire(int, int, eState);
	void checkVictoireCrazy(int x, int y, eState color);
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
	bool Finalstate;
	eState currentColor;
	int heuristic;
	Input move;
};


#endif
