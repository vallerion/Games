#ifndef GAME_H
#define GAME_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include <list>
using std::list;

#include "Entity.hpp"
#include "Player.hpp"
#include "Block.hpp"
#include "ball.hpp"

#include "Button.h"
using namespace VisualControlComponent;

class Game
{
private:
	sf::RenderWindow *window;
	sf::Clock *clock;
	sf::Event *event;
	float time;
	bool win;
	
	sf::Image *imageHP, *imageScore;
	sf::Texture *textureHP;
	sf::Sprite *spriteHP;
	sf::Sprite *backSprt;

	ButText *newGame;
	ButText *quit;
	ButPause *pause;

	Player *player;
	Ball *ball;
	list<Block*> blockList;

	static int level;

	void GameProcess();

	void Menu();

	void Pause(Player&, Ball&);

	void Level(sf::Texture&, sf::Image&, sf::Texture&);

public:
	Game();

	~Game();
};



#endif