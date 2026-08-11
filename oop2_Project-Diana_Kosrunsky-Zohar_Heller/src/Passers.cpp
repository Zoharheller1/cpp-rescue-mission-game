#include"Passers.h"
#include <memory> 


Passers::Passers(const char pic, const sf::Vector2f& location) : DynamicActives(pic, location,10, Resources::PASSER, Action::WALKING, 0.1f)
{
    setWalkComponent(std::make_unique<Moving>(30.f));
    setDirectionComponent(std::make_unique<RandomDirection>());
}

bool Passers::m_registerit = Factory<DynamicActives>::registerit("Passers",
    [](const char pic, const sf::Vector2f& location) -> std::unique_ptr<DynamicActives> { return std::make_unique<Passers>(pic, location); });

std::unique_ptr<DynamicActives> Passers::updateDynamicActicve(const sf::Time& deltaTime)
{

    if (m_DirectionComponent && (rand() % 1000 < 10))
        m_DirectionComponent->doMyAlgorithm(getSprite(), getDirection());

    updateAnimation(deltaTime);
 
    if (m_walkComponent && isAlive())
    {
        m_walkComponent->doMove(deltaTime, getSprite(), getDirection(), getLocation());
    }
    else
    {
        changeAction(Action::DEAD);
        addDeadTime(deltaTime);
    }  
    return nullptr;   
}

