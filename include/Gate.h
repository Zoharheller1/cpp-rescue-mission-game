#pragma once
#include <SFML/Graphics.hpp>
#include "Factory.h"
#include "ReplacePicture.h"

class Gate :public ReplacePicture
{
public:
	Gate(const char pic, const sf::Vector2f& location);
	virtual void handleCollisionWithBullet() override;
private:

	static bool m_registerit;
};