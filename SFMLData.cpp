#include "SFMLData.hpp"

SFMLData::SFMLData()
{
	win = new sf::RenderWindow(sf::VideoMode(1000, 1000), "My window");
	font = new sf::Font();
	texture = new sf::Texture();
	background = new sf::RectangleShape(sf::Vector2f(800, 800));

	if (!font->loadFromFile("SPECIAL.TTF"))
	{
		std::cerr << "WTF FONT CANT BE OPEN" << std::endl;
		exit(-1);
	}
	if (!texture->loadFromFile("table.jpg"))
	{
		std::cerr << "WTF TExture CANT BE OPEN" << std::endl;
		exit(-1);
	}
	background->setPosition(100, 100);
	//texture->setRepeated(true);
	texture->setSmooth(true);
	background->setTexture(texture);
	game = NULL;
	mainMenu[0] = "play";
	mainMenu[1] = "ia : ";
	mainMenu[2] = "quit";
	//background->setFillColor(sf::Color(40,40,40));


}

void SFMLData::Draw(eState color)
{
	win->clear(sf::Color::Black);
	win->draw(*background);
	DrawNormalMode(color);
	win->display();
}

bool SFMLData::DrawMainMenu(Input input, bool *noIa, int *choice, bool *menu)
{
	win->clear(sf::Color::Black);
	sf::Text menuEntry;

	menuEntry.setFont(*font);
	menuEntry.setCharacterSize(35);


	if (input.GetType() == UP)
		*choice = ((*choice - 1 >= 0) ? (*choice - 1) : 2);
	else if (input.GetType() == DOWN)
		*choice = (*choice + 1 < 3) ? (*choice + 1) : 0;
	else if (input.GetType() == VALIDATE && *choice == 0)
	{
		*menu = false;
		std::cout << "draw" << std::endl;
		Draw(WHITE);
		return true;
	}
	else if (input.GetType() == VALIDATE && *choice == 1)
		*noIa = !*noIa;
	else if (input.GetType() == VALIDATE && *choice == 2)
		return false;

	int i = 0;
	while (i < 3)
	{
		if (i == *choice)
			menuEntry.setColor(sf::Color::Red);
		else
			menuEntry.setColor(sf::Color::White);
		menuEntry.setString(mainMenu[i] + (i == 1 ? (!*noIa ? "ON" : "OFF") : ""));
		menuEntry.setPosition(400, 400 + i * 100);
		win->draw(menuEntry);
		i++;
	}
	win->display();
	return true;
}

void SFMLData::SetGameState(GameState *myEffeilTower)
{
	game = myEffeilTower;
}


void SFMLData::DrawHiScoreMenu()
{

}

void SFMLData::DrawNormalMode(eState cur)
{
	if (game == NULL)
		return;
	auto truc = game->GetMap();
	auto machin = game->GetCoups();
	std::string str("NOIR : ");
	str.append(std::to_string(game->GetCapture(BLACK)));
	str.append(" - BLANC : ");
	str.append(std::to_string(game->GetCapture(WHITE)));
	sf::Text score;
	score.setFont(*font);
	score.setCharacterSize(35);
	score.setPosition(20, 20);
	score.setString(str.c_str());
	win->draw(score);
	for (int i = 0; i < 19 * 19; i++)
	{
		bool prout = true;
		if (truc[i] == BLACK)
		{
			sf::CircleShape shape(10);
			shape.setFillColor(sf::Color(0, 0, 0));

			shape.setPosition(i % 19 * CASESIZE + 110, i / 19 * CASESIZE + 110);
			win->draw(shape);
		}
		else if (truc[i] == WHITE)
		{
			sf::CircleShape shape(10);
			shape.setFillColor(sf::Color(250, 250, 250));

			shape.setPosition(i % 19 * CASESIZE + 110, i / 19 * CASESIZE + 110);
			win->draw(shape);
		} 
		else if (machin[i].nb > 0)
		{
			prout = false;
			sf::CircleShape shape(10);
			shape.setFillColor(sf::Color(250, 0, 0));

			shape.setPosition(i % 19 * CASESIZE + 110, i / 19 * CASESIZE + 110);
			win->draw(shape);
		}
		// std::cout << machin[i].getNb() << " ";
		// if (i && !((i + 1) % 19))
		// 	std::cout << std::endl;
		if (cur == BLACK ? machin[i].blackForbiden : machin[i].whiteForbiden)
		{
			sf::CircleShape shape(10);
			shape.setFillColor(sf::Color(0, 250, 0));

			shape.setPosition(i % 19 * CASESIZE + 110, i / 19 * CASESIZE + 110);
			win->draw(shape);
		}
	}
	// std::cout << std::endl;
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
	win->clear(sf::Color::Black);
	win->draw(*background);
	sf::Text menuEntry;
	std::string str("NOIR : ");
	str.append(std::to_string(game->GetCapture(BLACK)));
	str.append(" - BLANC : ");
	str.append(std::to_string(game->GetCapture(WHITE)));
	sf::Text score;
	score.setFont(*font);
	score.setCharacterSize(35);
	score.setPosition(20, 20);
	score.setString(str.c_str());
	win->draw(score);


	menuEntry.setFont(*font);
	menuEntry.setCharacterSize(35);
	auto truc = game->GetMap();
	for (int i = 0; i < 19 * 19; i++)
	{
		if (truc[i] == BLACK)
		{
			sf::CircleShape shape(10);
			shape.setFillColor(sf::Color(0, 0, 0));

// set a 10-pixel wide orange outline
			shape.setPosition(i % 19 * CASESIZE + 110, i / 19 * CASESIZE + 110);
			win->draw(shape);
		}
		else if (truc[i] == WHITE)
		{
			sf::CircleShape shape(10);
			shape.setFillColor(sf::Color(250, 250, 250));

// set a 10-pixel wide orange outline
			shape.setPosition(i % 19 * CASESIZE + 110, i / 19 * CASESIZE + 110);
			win->draw(shape);
		}
	}

       // int i = 0;
       // while (i < NBACTIONEND)
       // {
       // 		if (i == choice)
       // 			menuEntry.setColor(sf::Color::Red);
       // 		else
	menuEntry.setColor(sf::Color::White);
	//menuEntry.setString();
	menuEntry.setPosition(20, 900);
	win->draw(menuEntry);
	win->display();
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

Input SFMLData::GetInput()
{
	sf::Event event;
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
			if (event.key.code == sf::Keyboard::Escape)
				return Input(ESC);
			else if (event.key.code == sf::Keyboard::Up)
				return Input(UP);
			else if (event.key.code == sf::Keyboard::Down)
				return Input(DOWN);
			else if (event.key.code == sf::Keyboard::Return)
				return Input(VALIDATE);
			return Input(NOINPUT);
		}
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				return Input(MOUSE, (event.mouseButton.x - 100) / CASESIZE, (event.mouseButton.y - 100) / CASESIZE);
			}
		}

	}
	return Input(NOINPUT);
}


SFMLData::~SFMLData()
{
	delete font;
	delete win;
}
