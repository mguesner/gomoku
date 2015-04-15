#ifndef GAME_HPP
#define GAME_HPP

#include "GameState.hpp"

class Game
{
public:
	Game();
	Game(Game const & src);
	Game& operator=(Game const & rhs);
	~Game();
private:
	GameState actual;
};

#endif
