#include "suicideBomber.h"
#include <memory> 
#include <cmath>
#include <iostream>

suicideBomber::suicideBomber(const char pic, const sf::Vector2f& location) : PlayerSeeking(pic,location,10, Resources::SUICIDEBOMBER, Action::WALKING,0.1f)
{
    setWalkComponent(std::make_unique<Moving>(70.f));
    
}

bool suicideBomber::m_registerit = Factory<PlayerSeeking>::registerit("SuicideBomber",
    [](const char pic, const sf::Vector2f& location) -> std::unique_ptr<PlayerSeeking> { return std::make_unique<suicideBomber>(pic, location); });


std::unique_ptr<DynamicActives> suicideBomber::updateDynamicActicve(const sf::Time& deltaTime)
{
    m_delta = deltaTime;
    auto playerLoc = getPlayerLocation();
    updateAnimation(deltaTime);
    if (isAlive())
    {
        if (m_DirectionComponent)m_DirectionComponent->doMyAlgorithm(getSprite(), playerLoc);

        setDirection({ std::cosf(getSprite().getRotation() * M_PI / 180.0f), std::sinf(getSprite().getRotation() * M_PI / 180.0f) });
        if (isCloseEnough(200) && m_walkComponent)
        {
            changeAction(Action::WALKING);
            m_walkComponent->doMove(deltaTime, getSprite(), getDirection(),getLocation());
        }
        if ((abs(getLocation().x - getPlayerLocation().x) <= 200.f) && (abs(getLocation().y - getPlayerLocation().y) <= 200.f))
            changeAction(Action::HANDSUP);
    }
    else {addDeadTime(deltaTime);}

    return nullptr;
}

bool suicideBomber::collisionWithPlayer()
{
    if (collision(0.7f,10))
    {
        setSpriteLocation(getPlayerLocation());
        changeAction(Action::MEDIUMBOMBER);
        return true;
    }
    return false;
}

    
