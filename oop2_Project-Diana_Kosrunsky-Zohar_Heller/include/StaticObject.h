#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"

class StaticObject :public Object
{
public:
	StaticObject(const char pic, const sf::Vector2f& location);
	virtual ~StaticObject() = default;
private:

};