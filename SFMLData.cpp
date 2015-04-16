#include "SFMLData.hpp"

SFMLData::SFMLData()
{
	win = new sf::RenderWindow(sf::VideoMode(1000, 1000), "My window");
	font = new sf::Font();
	texture = new sf::Texture();
	background = new sf::RectangleShape(sf::Vector2f(800, 800));

	// if (!font->loadFromFile("SPECIAL.TTF"))
	// {
	// 	std::cerr << "WTF FONT CANT BE OPEN" << std::endl;
	// 	exit(-1);
	// }
	if (!texture->loadFromFile("table.jpg"))
	{
		std::cerr << "WTF TExture CANT BE OPEN" << std::endl;
		exit(-1);
	}
	background->setPosition(100, 100);
	//texture->setRepeated(true);
	texture->setSmooth(true);
	background->setTexture(texture);
	//background->setFillColor(sf::Color(40,40,40));


}

void SFMLData::Draw()
{
	win->clear(sf::Color::Black);
	win->draw(*background);
	DrawNormalMode();
	win->display();
}

void SFMLData::DrawMainMenu()
{
       sf::Text menuEntry;

       menuEntry.setFont(*font);
       menuEntry.setCharacterSize(35);


       //int i = 0;
       // while (i < SIZEMENUCHOICES)
       // {
       // 		if (i == choice)
       // 			menuEntry.setColor(sf::Color::Red);
       // 		else
       // 			menuEntry.setColor(sf::Color::White);
       // 		menuEntry.setString(mainMenu[i] + (i == WALL ? (wall ? "ON" : "OFF") : ""));
       // 		menuEntry.setPosition(950, 500 + i * 100);
       // 		win->draw(menuEntry);
       // 		i++;
       // }
}

void SFMLData::SetGameState(Gamestate *myEffeilTower)
{
	game = myEffeilTower;
}


void SFMLData::DrawHiScoreMenu()
{

}

void SFMLData::DrawNormalMode()
{

}

void SFMLData::DrawMultiMode()
{

}

void SFMLData::DrawHostMenu()
{

}

void SFMLData::DrawJoinMenu()
{
}

void SFMLData::DrawMulti()
{

}

void SFMLData::DrawMultiMenu()
{
}

void SFMLData::DrawPauseMenu()
{
	sf::Text menuEntry;

       menuEntry.setFont(*font);
       menuEntry.setCharacterSize(35);


       // int i = 0;
       // while (i < NBACTIONPAUSE)
       // {
       // 		if (i == choice)
       // 			menuEntry.setColor(sf::Color::Red);
       // 		else
       // 			menuEntry.setColor(sf::Color::White);
       // 		menuEntry.setString(pauseMenu[i]);
       // 		menuEntry.setPosition(950, 500 + i * 100);
       // 		win->draw(menuEntry);
       // 		i++;
       // }
}

void SFMLData::DrawEndMenu()
{
	sf::Text menuEntry;

       menuEntry.setFont(*font);
       menuEntry.setCharacterSize(35);


       // int i = 0;
       // while (i < NBACTIONEND)
       // {
       // 		if (i == choice)
       // 			menuEntry.setColor(sf::Color::Red);
       // 		else
       // 			menuEntry.setColor(sf::Color::White);
       // 		menuEntry.setString(endMenu[i]);
       // 		menuEntry.setPosition(950, 500 + i * 100);
       // 		win->draw(menuEntry);
       // 		i++;
       // }
}

void SFMLData::DrawBestEndMenu()
{

}

void SFMLData::SetInput(int keycode)
{
	//value = keycode;
	(void)keycode;
}

int SFMLData::GetInput()
{
	sf::Event event;
	int ret = 0;
    while (win->pollEvent(event))
    {
            if (event.type == sf::Event::Closed)
            {
            	//emergency close
            	win->close();
            	exit(0);
            }
            else if (event.type == sf::Event::KeyPressed)
            {
            	ret = (int)sf::Event::KeyPressed;
            }

    }
	return ret;
}


SFMLData::~SFMLData()
{
	delete font;
	delete win;
}
