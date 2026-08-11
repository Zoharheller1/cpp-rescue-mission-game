#pragma once
#include <SFML/Graphics.hpp>
#include "House.h"
#include "Factory.h"
#include "MiniMap.h"

class HouseWithoutPrisoner :public House
{
public:
	HouseWithoutPrisoner(const char pic, const sf::Vector2f& location);
	virtual void handleCollisionWithBullet() override;
private:
	static bool m_registerit;
};