#include"SimpleSolider.h"
#include "Action.h"


SimpleSolider::SimpleSolider(const char pic, const sf::Vector2f& location) : PlayerSeeking(pic, location,10, Resources::SIMPLESOLIDER, Action::WALKING, 0.2f)
{
    setWalkComponent(std::make_unique<Moving>(59.f));
    setShootComponent(std::make_unique<Shooter>(1000.f));

}


bool SimpleSolider::m_registerit = Factory<PlayerSeeking>::registerit("SimpleSolider",
    [](const char pic, const sf::Vector2f& location) -> std::unique_ptr<PlayerSeeking> { return std::make_unique<SimpleSolider>(pic, location); });


std::unique_ptr<DynamicActives> SimpleSolider::updateDynamicActicve(const sf::Time& deltaTime)
{
    static int moveCounter = 0;
    static int stopCounter = 0;
    static int moveDuration = 2000;
    static int stopDuration = 2000;

    updateAnimation(deltaTime);
    if (isCloseEnough(100) && m_shootComponent && m_walkComponent && isAlive())
    {   
        auto playerLoc = getPlayerLocation();
        if (m_DirectionComponent)m_DirectionComponent->doMyAlgorithm(getSprite(), playerLoc);

        if (moveCounter < moveDuration)
        {
            changeAction(Action::WALKING);
            setDirection({ std::cosf(getSprite().getRotation() * M_PI / 180.0f), std::sinf(getSprite().getRotation() * M_PI / 180.0f) });
            m_walkComponent->doMove(deltaTime, getSprite(), getDirection(), getLocation());
            moveCounter += deltaTime.asMilliseconds();
        }
        else if (stopCounter < stopDuration)
        {

            if (stopCounter == 0)
            {   
                std::unique_ptr<DynamicActives> bullet = m_shootComponent->shoot(getSprite().getPosition(), "Rifle", getSprite().getRotation());
                stopCounter += deltaTime.asMilliseconds();
                if (bullet) changeAction(Action::SHOOTIONG);
                return bullet;
            }
            else if (stopCounter >= 500) changeAction(Action::STANDING);

            stopCounter += deltaTime.asMilliseconds();
        }

        if (stopCounter >= stopDuration)
        {
            moveCounter = 0;
            stopCounter = 0;
        }
    }
    else if (!isAlive())
    {
        changeAction(Action::DEAD);
        addDeadTime(deltaTime);
    }
    return nullptr;
}