#include "Board.h"
#include <iostream>
#include "Gate.h"
#include "Cannon.h"
#include "Scenery.h"
#include <SFML/Graphics.hpp>
#include "GamePlay.h"
#include <algorithm>
#include < memory >
#include <random>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>

void Board::newGame(MiniMap& minimap, Player& player)
{
	std::vector<sf::Vector2f> staticPositions = readPositionsFromFile("staticPositions.txt");
	std::vector<sf::Vector2f> dynamicOutMilitaryBasePositions = readPositionsFromFile("dynamicOutMilitaryBasePositions.txt");
	std::vector<sf::Vector2f> dynamicInsideBasePositions = readPositionsFromFile("dynamicInsideBasePositions.txt");
	std::vector<sf::Vector2f> houses  = readPositionsFromFile("houses.txt");

	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(staticPositions.begin(), staticPositions.end(), g);
	std::shuffle(dynamicOutMilitaryBasePositions.begin(), dynamicOutMilitaryBasePositions.end(), g);
	std::shuffle(dynamicInsideBasePositions.begin(), dynamicInsideBasePositions.end(), g);
	std::shuffle(houses.begin(), houses.end(), g);
	
	std::map<std::pair<std::string, char>, int> staticObjectTypes = 
	{
		{{"PresentGun", grende}, 4}, {{"PresentLife", heart}, 4}, {{"PresentShild", shild}, 4}, {{"PresentTime", Clock}, 2},
		{{"Scenery", skeletons}, 2}, {{"Scenery", skeleton}, 2}, {{"Scenery", tree}, 4}, {{"Scenery", dTree}, 1},
		{{"Scenery", bush}, 3}, {{"Scenery", stone}, 2}, {{"Scenery", dCar}, 2}
	};
	
	std::map<std::pair<std::string, char>, int> dynamicOutMilitaryBasePositionsTypes = 
	{
		 {{"Guard", AnimationPic}, 3}, {{"Cannon", weaponAnimation}, 3}
	};

	std::map<std::pair<std::string, char>, int> dynamicInsideMilitaryBasePositionsTypes =
	{
		 {{"SimpleSolider", AnimationPic}, 13}, {{"SuicideBomber", AnimationPic}, 5}, {{"Tank", weaponAnimation}, 2}
	};	

	initializeHouses(houses,minimap);
	
	addStaticObjects(staticPositions, staticObjectTypes);

	addDynamicObjects(dynamicOutMilitaryBasePositions, dynamicOutMilitaryBasePositionsTypes, player);

	addDynamicObjects(dynamicInsideBasePositions, dynamicInsideMilitaryBasePositionsTypes, player);

	addPermanentPlaces(player);

}


std::vector<sf::Vector2f> Board::readPositionsFromFile(const std::string& filename)
{
	std::vector<sf::Vector2f> positions;
	std::ifstream file(filename);
	std::string line;

	try {
		if (!file.is_open()) {
			throw std::runtime_error("Unable to open file: " + filename);
		}

		while (std::getline(file, line))
		{
			std::stringstream ss(line);
			float x, y;
			char comma;

			if (!(ss >> x >> comma >> y)) {
				std::string error_message = ("Error reading position from line: " + line);
				throw std::runtime_error(error_message);
			}

			if (x < 0 || x>2600 || y < 0 || y  > 5000)
			{
				std::string error_location =( "Error Lcation in line " +line);
				throw std::runtime_error(error_location);
			}
			

			positions.push_back(sf::Vector2f(x, y));
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "An error occurred while reading positions from the file: " << e.what() << std::endl;
		file.close();  
		exit(EXIT_FAILURE);;
	}

	file.close();  
	return positions;
}


void Board::addDynamicActives(const sf::Vector2f& position,const std::string type, const char pic)
{
	m_dynamicActicve.push_back(Factory<DynamicActives>::create(type, pic, position));
}

void Board::addStaticObjectFunc(const sf::Vector2f& position,const std::string type, const char pic)
{
	m_static.push_back(Factory<StaticObject>::create(type, pic, position));
}

void Board::initializeHouses(const std::vector<sf::Vector2f>& positions, MiniMap& minimap)
{

	for (int i = 0; i < 10; i++)
	{
		if (i < 3)
		{
			auto houseWithPrisoner = Factory<HouseWithPrisoner>::create("HouseWithPrisoner", 'O', positions[i]);

			houseWithPrisoner->setAddStaticObjectFunction([this](const sf::Vector2f& position, std::string type, const char pic)
				{
					addStaticObjectFunc(position, type, pic);
				});

			houseWithPrisoner->setAddEnemyObjectFunction([this](const sf::Vector2f& position, std::string type, const char pic)
				{
					addDynamicActives(position, type, pic);
				});

			houseWithPrisoner->attachObserver(&minimap);
			minimap.addHouse(positions[i]);
			m_static.push_back(std::move(houseWithPrisoner));
		}
		else
		{
			auto housewithout = Factory<HouseWithoutPrisoner>::create("HouseWithoutPrisoner", 'O', positions[i]);

			housewithout->setAddStaticObjectFunction([this](const sf::Vector2f& position, std::string type, const char pic)
				{
					addStaticObjectFunc(position, type, pic);
				});

			housewithout->attachObserver(&minimap);
			minimap.addHouse(positions[i]);
			m_static.push_back(std::move(housewithout));
		}
	}
}

void Board::addPermanentPlaces( Player& player)
{
	addPassers();

	auto wall1 = Factory<StaticObject>::create("Scenery", 'E', sf::Vector2f(610, 1000));
	m_static.push_back(std::move(wall1));

	auto wall2 = Factory<StaticObject>::create("Scenery", 'E', sf::Vector2f(1950, 1000));
	m_static.push_back(std::move(wall2));


	auto gate = Factory<ReplacePicture>::create("Gate", 'F', sf::Vector2f(1280, 1000));
	gate->setAddStaticObjectFunction([this](const sf::Vector2f& position, std::string type, const char pic)
		{
			addStaticObjectFunc(position, type, pic);
		});
	m_static.push_back(std::move(gate));

	auto helicopter = Factory<Helicopter>::create("Helicopter", 'R', sf::Vector2f(2350, 4800));
	player.attach(helicopter.get());
	helicopter->setAddStaticObjectFunction([this](const sf::Vector2f& position, std::string type, const char pic)
		{
			addStaticObjectFunc(position, type, pic);
		});
	helicopter->createSpot();
	m_dynamicActicve.push_back(std::move(helicopter));

	

}

void Board::addPassers()
{
	auto passer1 = Factory<DynamicActives>::create("Passers", AnimationPic, sf::Vector2f(400, 730));
	m_dynamicActicve.push_back(std::move(passer1));

	auto passer2 = Factory<DynamicActives>::create("Passers", AnimationPic, sf::Vector2f(2000, 600));
	m_dynamicActicve.push_back(std::move(passer2));

	auto passer3 = Factory<DynamicActives>::create("Passers", AnimationPic, sf::Vector2f(300, 300));
	m_dynamicActicve.push_back(std::move(passer3));
}

void Board::addStaticObjects(const std::vector<sf::Vector2f>& positions, std::map<std::pair<std::string, char>, int>& objectTypes)
{
	auto posIter = positions.begin();
	for (const auto& [typeCharPair, count] : objectTypes)
	{
		const auto& [type, charType] = typeCharPair;
		for (int i = 0; i < count && posIter != positions.end(); ++i, ++posIter)
		{
			auto obj = Factory<StaticObject>::create(type, charType, *posIter);
			m_static.push_back(std::move(obj));
		}
	}
}

void Board::addDynamicObjects(const std::vector<sf::Vector2f>& positions, std::map<std::pair<std::string, char>, int>& objectTypes, Player& player)
{
	auto posIter = positions.begin();
	for (const auto& [typeCharPair, count] : objectTypes)
	{
		const auto& [type, charType] = typeCharPair;
		for (int i = 0; i < count && posIter != positions.end(); ++i, ++posIter)
		{
			auto obj = Factory<PlayerSeeking>::create(type, charType, *posIter);
			player.attach(obj.get());
			m_dynamicActicve.push_back(std::move(obj));
		}
	}
}



void Board::addBullet(std::unique_ptr<DynamicActives> bullet)
{
	m_dynamicActicve.push_back(std::move(bullet));
}
void Board::drawStatic(sf::RenderWindow& window)
{
	std::for_each(m_static.begin(), m_static.end(), [&window](std::unique_ptr<StaticObject>& obj)
		{
			if (obj)
			{
				obj->draw(window);
			}
		});
}

void Board::drawDynamic(sf::RenderWindow& window)
{
	std::for_each(m_dynamicActicve.begin(), m_dynamicActicve.end(), [&window](std::unique_ptr<DynamicActives>& obj)
		{
			if (obj)
			{
				obj->draw(window);
			}
		});
}


void Board::updateEnemy( sf::Time deltaTime,Player &player)
{

	m_static.erase(std::remove_if(m_static.begin(), m_static.end(),
		[](const std::unique_ptr<StaticObject>& obj) {
			return obj && !obj->isAlive();
		}),
		m_static.end());


	m_dynamicActicve.erase(std::remove_if(m_dynamicActicve.begin(), m_dynamicActicve.end(),
		[&player](const std::unique_ptr<DynamicActives>& obj) {
			return obj && obj->deleteObj();
		}),
		m_dynamicActicve.end());

	size_t originalSize = m_dynamicActicve.size();
	for (size_t i = 0; i < originalSize; ++i)
	{
		if (m_dynamicActicve[i])
		{
			auto newEnemy = m_dynamicActicve[i]->updateDynamicActicve(deltaTime);
			if (newEnemy)
			{
				m_dynamicActicve.push_back(std::move(newEnemy));
			}
		}
	}
}

void Board::handleCollideDynamicActives()
{
	size_t originalEnemySize = m_dynamicActicve.size();
	size_t originalStaticSize = m_static.size();

	for (size_t i = 0; i < originalEnemySize; ++i)
	{
		for (size_t j = 0; j < originalStaticSize; ++j)
		{
			if (isCollide(*m_dynamicActicve[i], *m_static[j]))
			{
				processCollision(*m_dynamicActicve[i], *m_static[j]);
			}
		}
	}
	for (size_t i = 0; i < originalEnemySize; ++i)
	{
		for (size_t j = i+1; j < originalEnemySize; ++j)
		{
			if (isCollide(*m_dynamicActicve[i], *m_dynamicActicve[j]))
			{
				processCollision(*m_dynamicActicve[i], *m_dynamicActicve[j]);
			}
		}
	}
}



void Board::handleCollidePlayer(Player& player)
{
	for_each_pair(m_dynamicActicve.begin(), m_dynamicActicve.end(), player, [this](Player& player, auto& b) {
		if (isCollide(player, *b))
		{
			processCollision(player, *b);
		}
		});

	for_each_pair(m_static.begin(), m_static.end(), player, [this](Player& player, auto& b) {
		if (isCollide(player, *b))
		{
			processCollision(player, *b);
		}
		});

}



bool Board::isCollide(Object& a, Object& b)const
{
	if (&a == &b)
		return false;

	return (a.checkCollision(b));
}




