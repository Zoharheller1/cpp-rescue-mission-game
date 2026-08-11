#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"
#include "Marcos.h"
#include <cmath>
#include <ctime>
#include <memory>
#include <vector>

class Player;
class Object
{
public:

	Object(const sf::Texture& texture, const sf::Vector2f& location);
	Object(const char  pic, const sf::Vector2f& location);
	virtual ~Object() = default;

	virtual void draw(sf::RenderWindow&)const;

	void SetLocation(const sf::Vector2f&);
	void deadObject();

	bool isAlive()const;
	bool checkCollision(const Object& other)const;

	sf::Vector2f  getPosition() const; 
	sf::Sprite getSprite() const;
	
protected:

	sf::Sprite& getSprite();
	sf::Vector2f& getLocation();

	void setSpriteLocation(const sf::Vector2f& location);
private:

	sf::Vector2f m_location; 
	sf::Sprite m_sprite;

	bool m_toDeleat;
};
