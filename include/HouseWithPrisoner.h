#pragma once
#include <SFML/Graphics.hpp>
#include "House.h"
#include "Factory.h"
#include "MiniMap.h"

class HouseWithPrisoner :public House
{
public:
	HouseWithPrisoner(const char pic, const sf::Vector2f& location);
	virtual void handleCollisionWithBullet() override;
	void setAddEnemyObjectFunction(std::function<void(const sf::Vector2f& position, std::string type, const char pic)> addActiveFunc);
private:

	static bool m_registerit;
	std::function<void(const sf::Vector2f& position, std::string type, const char pic)> m_addEnemyFunc;
};