#include "Prisioner.h"
#include <memory> 


Prisioner::Prisioner(const char pic, const sf::Vector2f& location) : DynamicActives(pic, location,1, Resources::PRISIONER, Action::WALKING, 0.3f)
{
    setWalkComponent(std::make_unique<Moving>(70.f));

    setDirection ({ 0,-1 });
 }

bool Prisioner::m_registerit = Factory<DynamicActives>::registerit("Prisioner",
    [](const char pic, const sf::Vector2f& location) -> std::unique_ptr<DynamicActives> { return std::make_unique<Prisioner>(pic, location); });


std::unique_ptr<DynamicActives> Prisioner::updateDynamicActicve(const sf::Time& deltaTime)
{   
     updateAnimation(deltaTime);
     if (m_walkComponent && moveCounter <= 1000)
     {
         m_walkComponent->doMove(deltaTime, getSprite(), getDirection(), getLocation());
         moveCounter += deltaTime.asMilliseconds();
     }
     else  changeAction(Action::STANDING);
     return nullptr;
}