#ifndef MLXDATA_HPP
#define MLXDATA_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Gamestate.hpp"

#define WIDTH		1920
#define HEIGHT		1080
#define CASESIZE	42
class SFMLData
{
public:
	SFMLData();
	void Draw();
	void Close();
	void Lock();
	int GetInput();
	void SetInput(int);
	void SetGameState(GameState*);
	~SFMLData();

private:

	void		DrawMainMenu();
	void		DrawHiScoreMenu();
	void		DrawNormalMode();
	void		DrawMultiMode();
	void		DrawMulti();
	void		DrawMultiMenu();
	void		DrawHostMenu();
	void		DrawJoinMenu();
	void		DrawPauseMenu();
	void		DrawEndMenu();
	void		DrawBestEndMenu();

	int			x0;
	int			y0;
	sf::RenderWindow	*win;
	sf::Font 			*font;
	sf::Texture			*texture;
	sf::RectangleShape	*background;
	GameState			*game;
	//sf::Sprite			*sprite;
	//SFML_Surface	*screenSurface;
};

#endif
