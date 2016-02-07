#ifndef BUTTON_HPP
#define BUTTON_HPP

namespace VisualControlComponent
{
	class ButPause
	{
	private:
		sf::Sprite *sprite;
		float x, y;
		bool click;

		enum
		{
			pause,play
		}state;

	public:
		ButPause(sf::Texture &texture, float x, float y)
		{
			this->x = x;
			this->y = y;
			click = false;

			sprite = new sf::Sprite();
			sprite->setTexture(texture);
			sprite->setTextureRect(sf::IntRect(32, 36, 32, 36));
			sprite->setPosition(sf::Vector2f(x, y));
			state = play;
		}

		void Update(sf::RenderWindow &window, sf::Event &event)
		{
			click = false;
			if (state == play)
			{
				sprite->setTextureRect(sf::IntRect(32, 36, 32, 36));
				if (sf::IntRect(x, y, 32, 36).contains(sf::Mouse::getPosition(window)))
				{
					sprite->setTextureRect(sf::IntRect(32, 0, 32, 36));
					if (event.type == sf::Event::MouseButtonPressed)
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						click = true;
						state = pause;
						std::cout << "click!" << std::endl;
					}
				}
			}
			else
			{
				sprite->setTextureRect(sf::IntRect(0, 36, 32, 36));
				if (sf::IntRect(x, y, 32, 36).contains(sf::Mouse::getPosition(window)))
				{
					sprite->setTextureRect(sf::IntRect(0, 0, 32, 36));
					if (event.type == sf::Event::MouseButtonPressed)
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						click = true;
						state = play;
						std::cout << "click!" << std::endl;
					}
				}
			}
		}

		sf::Sprite *Render()
		{
			return sprite;
		}

		bool ClickPlay()
		{
			return click && state == play;
		}

		bool ClickPause()
		{
			return click && state == pause;
		}

		~ButPause()
		{
			delete sprite;
		}
	};

	class ButText
	{
	private:
		sf::Text *caption;
		sf::Font *font;
		float x, y;
		bool click;
	
	public:
		ButText(const char* caption, float x, float y)
		{
			this->x = x;
			this->y = y;
			click = false;

			font = new sf::Font();
			font->loadFromFile("res/MATURASC.TTF");
			this->caption = new sf::Text(caption, *font, 50);
			this->caption->setColor(sf::Color::Green);
			this->caption->setOrigin(this->caption->getLocalBounds().width / 2, this->caption->getLocalBounds().height / 2);
			this->caption->setPosition(sf::Vector2f(x, y));
		}

		void Update(sf::RenderWindow &window)
		{
			click = false;
			caption->setColor(sf::Color(0, 103, 58));
			if (sf::IntRect(x - this->caption->getLocalBounds().width / 2, y, caption->getLocalBounds().width, caption->getLocalBounds().height).contains(sf::Mouse::getPosition(window)))
			{
				caption->setColor(sf::Color(0, 60, 34));
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					click = true;
			}
		}

		bool Click()
		{
			return click;
		}

		sf::Text *Render()
		{
			return caption;
		}

		~ButText()
		{
			delete caption;
			delete font;
		}

	};
}

#endif