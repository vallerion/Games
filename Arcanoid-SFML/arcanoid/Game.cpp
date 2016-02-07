#include "Game.h"

int Game::level = 0;

void Game::Level(sf::Texture &back, sf::Image &imageBall, sf::Texture &textBlock)
{
	switch (level)
	{
	case 1:

		imageBall.loadFromFile("res/ball/ball_grey.png");
		back.loadFromFile("res/background/Backgrounds_Grey.jpg");
		textBlock.loadFromFile("res/block/block_grey.png");

		ball = new Ball(*player);
		ball->SetImage(imageBall);
		//for (int i = 250; i <= 750; i += 250)
			//blockList.push_back(new Block(textureBlock, i, 100, 5));
		blockList.push_back(new Block(textBlock, 500, 100, 5));
		break;

	case 2:

		imageBall.loadFromFile("res/ball/ball_green.png");
		back.loadFromFile("res/background/Backgrounds_Green.jpg");
		textBlock.loadFromFile("res/block/block_green.png");

		ball->SetImage(imageBall);
		
		blockList.push_back(new Block(textBlock, 500, 100, 5));

		break;
	case 3:

		imageBall.loadFromFile("res/ball/ball_orange1.png");
		back.loadFromFile("res/background/Backgrounds_Orange1.jpg");
		textBlock.loadFromFile("res/block/block_orange1.png");

		ball->SetImage(imageBall);

		blockList.push_back(new Block(textBlock, 500, 100, 5));

		break;

	case 4:

		imageBall.loadFromFile("res/ball/ball_red.png");
		back.loadFromFile("res/background/Backgrounds_Red.jpg");
		textBlock.loadFromFile("res/block/block_red.png");

		ball->SetImage(imageBall);

		blockList.push_back(new Block(textBlock, 500, 100, 5));

		break;

	case 5:

		imageBall.loadFromFile("res/ball/ball_orange2.png");
		back.loadFromFile("res/background/Backgrounds_Orange2.jpg");
		textBlock.loadFromFile("res/block/block_orange2.png");

		ball->SetImage(imageBall);

		blockList.push_back(new Block(textBlock, 500, 100, 5));

		break;
	default:
		break;
	}
}

Game::Game()
{
	window = new sf::RenderWindow(sf::VideoMode(1024, 640), "Arcanoid");
	clock = new sf::Clock();
	event = new sf::Event();

	newGame = new ButText("New game", 512, 250);
	quit = new ButText("Qiut", 512, 300);

	sf::Texture *text = new sf::Texture();
	text->loadFromFile("res/game/pause_play.png");
	pause = new ButPause(*text, window->getSize().x - 40, 40);

	while (1)
	{
		Menu();
		if (newGame->Click())
		{
			do
			{
				level++;
				GameProcess();				
			} while (win && level < 5);
		}
	}
}

void Game::Menu()
{
	sf::Texture *backMenu = new sf::Texture();
	backMenu->loadFromFile("res/background/backMenu.jpg");
	sf::Sprite *backSprt = new sf::Sprite(*backMenu);
	backSprt->setPosition(0, 0);

	while (window->isOpen())
	{
		while (window->pollEvent(*event))
		{
			if (event->type == sf::Event::Closed)
				window->close();
		}

		newGame->Update(*window);
		quit->Update(*window);
		if (quit->Click())
			window->close();
		if (newGame->Click())
			break;

		window->clear();		

		window->draw(*backSprt);
		window->draw(*newGame->Render());
		window->draw(*quit->Render());

		window->display();

		sf::sleep(sf::milliseconds(1));
	}

	delete backMenu;
	delete backSprt;
}

void Game::Pause(Player &player, Ball &ball)
{
	sf::Texture *textPause = new sf::Texture();
	textPause->loadFromFile("res/game/pause_screen.png");
	sf::Sprite *backPause = new sf::Sprite(*textPause);

	while (window->isOpen())
	{
		while (window->pollEvent(*event))
		{
			if (event->type == sf::Event::Closed)
				window->close();
			pause->Update(*window, *event);
		}

		
		if (pause->ClickPlay())
			break;

		window->clear();

		window->draw(*backSprt);
		window->draw(*player.Render());
		window->draw(*ball.Render());
		for (auto it = blockList.begin(); it != blockList.end() && (*it)->GetExist(); it++)
		{
			window->draw(*(*it)->Render());
		}
		
		for (int i = 30; ball.GetPlayerHP() && i <= ball.GetPlayerHP() * 30; i += 30)
		{
			spriteHP->setPosition(sf::Vector2f(window->getSize().x - i, 10));
			window->draw(*spriteHP);
		}

		window->draw(*backPause);
		window->draw(*pause->Render());

		window->display();

		sf::sleep(sf::milliseconds(1));
	}

	delete textPause;
	delete backPause;
}

void Game::GameProcess()
{
	// start: hp
	textureHP = new sf::Texture();
	textureHP->loadFromFile("res/game/playerhp.png");
	spriteHP = new sf::Sprite();
	spriteHP->setTexture(*textureHP);
	// end

	sf::Image *imageBall = new sf::Image();
	sf::Texture *backGame = new sf::Texture(),
				*textBlock = new sf::Texture();

	player = new Player();
	Level(*backGame, *imageBall, *textBlock);

	backSprt = new sf::Sprite(*backGame);
	backSprt->setPosition(0, 0);

	win = false;

	while (window->isOpen())
	{
		if (ball->GetPlayerHP() && blockList.empty())
		{
			win = true;
			break;
		}
		else if (!ball->GetPlayerHP())
		{
			delete ball;
			level = 1;			
			break;
		}

		time = clock->getElapsedTime().asMicroseconds() / 800;
		clock->restart();
		
		while (window->pollEvent(*event))
		{
			
			if (event->type == sf::Event::Closed)
				window->close();

			pause->Update(*window, *event);			
		}

		
		if (pause->ClickPause())
			Pause(*player, *ball);

		player->Physic(time);
		ball->Physic(*player, blockList, time);

		window->clear();

		window->draw(*backSprt);
		window->draw(*player->Render());
		window->draw(*ball->Render());
		for (auto it = blockList.begin(); it != blockList.end() && (*it)->GetExist(); it++)
		{
			window->draw(*(*it)->Render());
		}

		window->draw(*pause->Render());
		for (int i = 30; ball->GetPlayerHP() && i <= ball->GetPlayerHP() * 30; i += 30)
		{
			spriteHP->setPosition(sf::Vector2f(window->getSize().x - i, 10));
			window->draw(*spriteHP);
		}

		window->display();

		sf::sleep(sf::milliseconds(1));
	}

	delete imageScore;
	delete imageHP;
	delete imageBall;
	delete textBlock;
	delete backGame;
	delete backSprt;	
	delete player;
}

Game::~Game()
{
	for (auto it = blockList.begin(); it != blockList.end(); it++)
	{
		delete *it;
		blockList.erase(it);
		it = blockList.begin();
	}

	delete window;
	delete event;
	delete clock;
	delete newGame;
	delete quit;
	delete pause;
}