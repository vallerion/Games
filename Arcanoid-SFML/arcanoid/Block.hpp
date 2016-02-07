#ifndef BLOCK_HPP
#define BLOCK_HPP

class Block : public Entity
{
private:
	sf::RectangleShape *recShape;
	sf::Texture &texture;

	bool isExist;
	int healhPoint;

	void Control(float){};

public:
	Block(sf::Texture &texture, float x, float y, int hp) : texture(texture)
	{
		recShape = new sf::RectangleShape(sf::Vector2f(100, 40));
		recShape->setTexture(&texture);
		recShape->setTextureRect(sf::IntRect(0, 0, 100, 40));
		recShape->setOrigin(sf::Vector2f(50, 20));
		recShape->setPosition(sf::Vector2f(x, y));

		healhPoint = hp;

		isExist = true;
	}

	int IncHP()
	{
		if (healhPoint == 1)
			isExist = false;
		else if (healhPoint == 5)
			recShape->setTextureRect(sf::IntRect(100, 0, 100, 40));
		else if (healhPoint == 3)
			recShape->setTextureRect(sf::IntRect(200, 0, 100, 40));
		else if (healhPoint == 2)
			recShape->setTextureRect(sf::IntRect(300, 0, 100, 40));

		return --healhPoint;
	}

	bool GetExist()
	{
		return isExist;
	}

	sf::Shape *Render()
	{
		return recShape;
	}

	~Block()
	{
		delete recShape;
	}

};


#endif