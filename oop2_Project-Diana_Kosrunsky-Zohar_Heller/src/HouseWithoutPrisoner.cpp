#include "HouseWithoutPrisoner.h"
#include "Board.h"
#include "Ruins.h"

HouseWithoutPrisoner::HouseWithoutPrisoner(const char pic, const sf::Vector2f& location) :House(pic, location) {}

void HouseWithoutPrisoner::handleCollisionWithBullet() {House::handleCollisionWithBullet();}


bool HouseWithoutPrisoner::m_registerit = Factory<HouseWithoutPrisoner>::registerit("HouseWithoutPrisoner",
    [](const char pic, const sf::Vector2f& location) -> std::unique_ptr<HouseWithoutPrisoner> { return std::make_unique<HouseWithoutPrisoner>(pic, location); });

