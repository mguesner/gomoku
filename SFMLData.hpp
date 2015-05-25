#ifndef MLXDATA_HPP
#define MLXDATA_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Gamestate.hpp"
#include "Sound.hpp"
#include "Input.hpp"

#define WIDTH		1920
#define HEIGHT		1080
#define CASESIZE	42

class SFMLData
{
public:
	SFMLData();
	void Draw(eState);
	void Close();
	void Lock();
	Input GetInput();
	void SetInput(int);
	void SetGameState(GameState*);
	void		DrawMainMenu(Input input, bool *noIa, int *choice, bool *menu);
	void		DrawEndMenu(std::exception *e);
	void		Parameters(Sound *music);
	~SFMLData();

private:

	void		DrawHiScoreMenu();
	void		DrawNormalMode(eState);
	void		DrawMultiMode();
	void		DrawMulti();
	void		DrawMultiMenu();
	void		DrawHostMenu();
	void		DrawJoinMenu();
	void		DrawPauseMenu();
	void		DrawBestEndMenu();

	int			x0;
	int			y0;
	Sound	*actualSound;
	sf::RenderWindow	*win;
	sf::Font 			*font;
	sf::Texture			*texture;
	sf::RectangleShape	*background;
	GameState			*game;
	std::string			mainMenu[3];
	//sf::Sprite			*sprite;
	//SFML_Surface	*screenSurface;
};

#endif
