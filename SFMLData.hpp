#ifndef MLXDATA_HPP
#define MLXDATA_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#define WIDTH		1920
#define HEIGHT		1080

class SFMLData
{
public:
	SFMLData();
	void Draw();
	void Close();
	void Lock();
	int GetInput();
	void SetInput(int);
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
	//sf::Sprite			*sprite;
	//SFML_Surface	*screenSurface;
};

#endif
