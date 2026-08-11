#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"
#include "StaticObject.h"
#include <functional>

class Board;
class ReplacePicture :public StaticObject
{
public:
	ReplacePicture(const char pic, const sf::Vector2f& location);
	virtual ~ReplacePicture() = default;

	void setAddStaticObjectFunction(std::function<void(const sf::Vector2f& position, std::string type, const char pic)> addStaticFunc);
	virtual void handleCollisionWithBullet() = 0;

protected:
	std::function<void(const sf::Vector2f& position, std::string type, const char pic)> m_addStaticFunc;
};
