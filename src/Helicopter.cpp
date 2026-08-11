#include "Helicopter.h"
#include "Spot.h"


bool Helicopter::m_registerit = Factory<Helicopter>::registerit("Helicopter",
    [](const char pic, const sf::Vector2f& location) -> std::unique_ptr<Helicopter> { return std::make_unique<Helicopter>(pic, location); });

Helicopter::Helicopter(const char pic, const sf::Vector2f& location) :PlayerSeeking(pic, location, 7, Resources::HELICOPTER, Action::STANDING, 0.03f) {}

std::unique_ptr<DynamicActives> Helicopter::updateDynamicActicve(const sf::Time& deltaTime)
{
	if (isCloseEnough(300)) updateAnimation(deltaTime);
	return NULL;
}


void Helicopter::createSpot() 
{
    sf::Vector2f spotLocation = getPosition();
    spotLocation.x -= 300;
    auto spot = Factory<StaticObject>::create("Spot", 'W', spotLocation);
    if (spot) {m_addStaticFunc(spotLocation, "Spot", 'W');}
}

void Helicopter::setAddStaticObjectFunction(std::function<void(const sf::Vector2f& position, std::string type, const char pic)> addStaticFunc)
{
    m_addStaticFunc = addStaticFunc;
}


