#ifndef BALL_HPP
#define BALL_HPP

class Ball : public Entity
{
private:
	sf::CircleShape *circle;
	sf::Texture *texture;

	int playerHP;

	enum
	{
		stop,move
	}state;

	struct
	{
		double x, y;
		double dx, dy;
	}coordinate;

	void Control(float time)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			std::cout << "space!";
			if (state == stop)
			{
				coordinate.dy = -0.4;
				state = move;
			}
		}
	}

public:
	Ball(Player &object)
	{
		circle = new sf::CircleShape(8);
		texture = new sf::Texture();

		circle->setOrigin(sf::Vector2f(8, 8));

		coordinate.x = object.Render()->getPosition().x;
		coordinate.y = object.Render()->getPosition().y - 8;
		coordinate.dx = coordinate.dy = 0;
		circle->setPosition(sf::Vector2f(coordinate.x, coordinate.y));

		state = stop;
		playerHP = 3;
	}

	void SetImage(sf::Image &image)
	{
		texture->loadFromImage(image);
		circle->setTexture(texture);
	}

	void Physic(Player &objPlayer, list<Block*> &listBlock, float time)
	{
		Control(time);

		if (state == stop)
		{
			coordinate.x = objPlayer.Render()->getPosition().x;
			coordinate.y = objPlayer.Render()->getPosition().y - 8;
			circle->setPosition(sf::Vector2f(coordinate.x, coordinate.y));
		}
		else
		{
			if (coordinate.y >= 650)
			{
				playerHP--;
				state = stop;
				coordinate.dx = 0;
			}

			if (coordinate.y <= 8)
			{
				coordinate.y = 8;
				coordinate.dy *= -1;				
			}
			else if (coordinate.x <= 8)
			{				
				coordinate.x = 8;
				coordinate.dx *= -1;
			}
			else if (coordinate.x >= 1016)
			{
				coordinate.x = 1016;
				coordinate.dx *= -1;
			}

			if (GetRect().intersects(objPlayer.GetRect()) && coordinate.dy > 0 && state == move)
			{
				coordinate.dy *= -1;

				if (circle->getPosition().x < objPlayer.Render()->getPosition().x)
					coordinate.dx = -(objPlayer.Render()->getPosition().x - circle->getPosition().x) * time * 0.01;
				else if (circle->getPosition().x > objPlayer.Render()->getPosition().x)
					coordinate.dx = (circle->getPosition().x - objPlayer.Render()->getPosition().x) * time * 0.01;
			}

			for (auto it = listBlock.begin(); it != listBlock.end(); it++)
			{
				if (GetRect().intersects((*it)->GetRect()))
				{
					if (coordinate.y + 7.6 >= (*it)->Render()->getPosition().y + (*it)->Render()->getOrigin().y || coordinate.y - 7.6 <= (*it)->Render()->getPosition().y - (*it)->Render()->getOrigin().y)
						coordinate.dy *= -1;
					if (coordinate.x + 7.6 >= (*it)->Render()->getPosition().x + (*it)->Render()->getOrigin().x || coordinate.x - 7.6 <= (*it)->Render()->getPosition().x - (*it)->Render()->getOrigin().x)
						coordinate.dx *= -1;

					std::cout << "coll" << std::endl;
					(*it)->IncHP();
				}
				if (!(*it)->GetExist())
				{
					delete *it;
					listBlock.erase(it);
					it = listBlock.begin();
				}
				
			}

		}

		coordinate.y += coordinate.dy * time;
		coordinate.x += coordinate.dx * time;
		circle->setPosition(sf::Vector2f(coordinate.x, coordinate.y));
	}

	int GetPlayerHP()
	{
		return playerHP;
	}

	sf::CircleShape *Render()
	{
		return circle;
	}

	~Ball()
	{
		delete circle;
	}

};


#endif