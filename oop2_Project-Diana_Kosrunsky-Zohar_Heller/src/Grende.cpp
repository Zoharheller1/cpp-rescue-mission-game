#include "Grende.h"
#include "DynamicActives.h"

bool Grende::m_registerit = Factory<Bullet>::registerit("Grende",
    [](const char pic, const sf::Vector2f& location) -> std::unique_ptr<Bullet> { return std::make_unique<Grende>(pic, location); });



Grende::Grende(const char pic, const sf::Vector2f& location) :Bullet(pic, location, Resources::GRENADE, 0.1f,180.f){}

std::unique_ptr<DynamicActives> Grende::updateDynamicActicve(const sf::Time& deltaTime)
{
    Bullet::updateDynamicActicve(deltaTime);

    if (endTime() || overBoard()) changeAction(Action::DEAD);

    return nullptr;
}


