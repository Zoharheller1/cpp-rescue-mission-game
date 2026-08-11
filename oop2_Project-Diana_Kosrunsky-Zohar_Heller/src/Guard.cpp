#include"Guard.h"



Guard::Guard(const char pic, const sf::Vector2f& location) : PlayerSeeking(pic, location,10,Resources::GUARD, Action::STANDING, 0.3f)
{
    
    setShootComponent(std::make_unique<Shooter>(2000.f));
  
}
bool Guard::m_registerit = Factory<PlayerSeeking>::registerit("Guard",
    [](const char pic, const sf::Vector2f& location) -> std::unique_ptr<PlayerSeeking> { return std::make_unique<Guard>(pic, location); });


std::unique_ptr<DynamicActives> Guard::updateDynamicActicve(const sf::Time& deltaTime)
{
    static int stopCounter = 0;
    auto playerLoc = getPlayerLocation();
    updateAnimation(deltaTime);
    if (m_DirectionComponent)m_DirectionComponent->doMyAlgorithm(getSprite(), playerLoc);

    if (isCloseEnough(100) && m_shootComponent && isAlive())
    {
        std::unique_ptr<DynamicActives> bullet = m_shootComponent->shoot(getSprite().getPosition(), "Rifle", getSprite().getRotation());
        if (bullet)
        {
            stopCounter = 0;
            changeAction(Action::SHOOTIONG);
            return bullet;
        }
        else if (stopCounter >= 800) changeAction(Action::STANDING);
    }
    else if (!isAlive())
    {
        changeAction(Action::DEAD);
        addDeadTime(deltaTime);
    }
    stopCounter += deltaTime.asMilliseconds();
    return nullptr;
}