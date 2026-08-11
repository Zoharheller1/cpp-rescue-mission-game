#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <memory>
#include <stdlib.h> 
#include <time.h>
#include "Marcos.h"
#include "MiniMap.h"
#include <string>
#include "StaticObject.h"
#include "DynamicActives.h"
#include "PlayerSeeking.h"
#include "CollisionHandling.h"
#include "HouseWithPrisoner.h"
#include "HouseWithoutPrisoner.h"
#include "Helicopter.h"

class Player;
class GamePlay;
class Board {

public:

	void newGame(MiniMap& minimap, Player& player);
	void handleCollideDynamicActives();
	void handleCollidePlayer(Player& player);
	void addBullet(std::unique_ptr<DynamicActives> bullet);
	void drawStatic(sf::RenderWindow& window);
	void drawDynamic(sf::RenderWindow& window);

	template <typename FwdIt, typename Fn>
	void for_each_pair(FwdIt begin, FwdIt end, Player& player, Fn fn);
	void updateEnemy( sf::Time deltaTime,Player &);
	template <typename FwdIt, typename Fn>
	void for_each_pair(FwdIt begin, FwdIt end, Fn fn);
	template <typename A, typename B, typename Fn>
	void for_each_pair(A beginA, A endA, B beginB, B endB, Fn fn);

	bool isCollide(Object& a, Object& b)const;

private:
	void addStaticObjectFunc(const sf::Vector2f& position,const std::string type, const char pic);
	void addDynamicActives(const sf::Vector2f& position,const std::string type, const char pic);
	void initializeHouses(const std::vector<sf::Vector2f>& positions, MiniMap& minimap);
	std::vector<sf::Vector2f> readPositionsFromFile(const std::string& filename);
	void addPermanentPlaces( Player& player);
	void addPassers();
	void addStaticObjects(const std::vector<sf::Vector2f>& positions, std::map<std::pair<std::string, char>, int>& objectTypes);
	void addDynamicObjects(const std::vector<sf::Vector2f>& positions, std::map<std::pair<std::string, char>, int>& objectTypes, Player& player);

	std::vector < std::unique_ptr <StaticObject >> m_static;
	std::vector < std::unique_ptr <DynamicActives >> m_dynamicActicve;
};

template <typename FwdIt, typename Fn>
void Board::for_each_pair(FwdIt begin, FwdIt end, Fn fn)
{
	for (; begin != end; ++begin)
		for (auto second = begin + 1; second != end; ++second)
			fn(*begin, *second);
}

template <typename A, typename B, typename Fn>
void Board::for_each_pair(A beginA, A endA, B beginB, B endB, Fn fn)
{
	for (; beginA != endA; ++beginA)
		for (auto second = beginB; second != endB; ++second)
			fn(*beginA, *second);
}
template <typename FwdIt, typename Fn>
void Board::for_each_pair(FwdIt begin, FwdIt end, Player& player, Fn fn)
{
	for (; begin != end; ++begin)
		fn(player, *begin);
}

