#ifndef ENTITY_HPP
#define ENTITY_HPP

class Entity
{
protected:
	//virtual void Control(float) = 0;

public:

	//virtual void Physic(float, ...) = 0;
	virtual sf::Shape *Render() = 0;
	
	sf::FloatRect GetRect()
	{
		return sf::FloatRect(Render()->getPosition().x - Render()->getOrigin().x, Render()->getPosition().y - Render()->getOrigin().y, Render()->getGlobalBounds().width, Render()->getGlobalBounds().height);
	}

	virtual ~Entity(){};

};

#endif