#include "HouseWithPrisoner.h"
#include "Board.h"
#include "Prisioner.h"
#include "Ruins.h"

HouseWithPrisoner::HouseWithPrisoner(const char pic, const sf::Vector2f& location) :House(pic, location), m_addEnemyFunc(nullptr) {}

void HouseWithPrisoner::handleCollisionWithBullet()
{
    if (isAlive() && m_addEnemyFunc)
    {
        m_addEnemyFunc(getSprite().getPosition(), "Prisioner", 'P');
    }

    House::handleCollisionWithBullet();


}


void HouseWithPrisoner::setAddEnemyObjectFunction(std::function<void(const sf::Vector2f& position, std::string type, const char pic)> addActiveFunc)
{
    m_addEnemyFunc = addActiveFunc;
}

bool HouseWithPrisoner::m_registerit = Factory<HouseWithPrisoner>::registerit("HouseWithPrisoner",
    [](const char pic, const sf::Vector2f& location) -> std::unique_ptr<HouseWithPrisoner> { return std::make_unique<HouseWithPrisoner>(pic, location); });

