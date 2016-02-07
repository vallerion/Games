#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player : public Entity
{
private:
	sf::RectangleShape *recShape;

	void Control(float time)
	{
		/*if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
				recShape->setPosition(sf::Vector2f(recShape->getPosition().x - 10. * time, recShape->getPosition().y));
			else if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
				recShape->setPosition(sf::Vector2f(recShape->getPosition().x + 10. * time, recShape->getPosition().y));
			std::cout << "press";
		}*/

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			recShape->setPosition(sf::Vector2f(recShape->getPosition().x - 0.5 * time, recShape->getPosition().y));
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			recShape->setPosition(sf::Vector2f(recShape->getPosition().x + 0.5 * time, recShape->getPosition().y));
	}

public:
	Player()
	{
		recShape = new sf::RectangleShape(sf::Vector2f(100, 10));
		recShape->setOrigin(sf::Vector2f(50, 0));
		recShape->setPosition(sf::Vector2f(512, 600));		
	}

	void Physic(float time)
	{
		Control(time);

		if (recShape->getPosition().x <= 50)
			recShape->setPosition(sf::Vector2f(50, recShape->getPosition().y));
		else if (recShape->getPosition().x >= 974)
			recShape->setPosition(sf::Vector2f(974, recShape->getPosition().y));
	}

	sf::Shape *Render()
	{
		return recShape;
	}

	~Player()
	{
		delete recShape;
	}

};

#endif