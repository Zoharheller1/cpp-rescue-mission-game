#include"Cannon.h"


Cannon::Cannon(const char pic, const sf::Vector2f& location) : PlayerSeeking(pic, location,25, Resources::CANNON, Action::STANDING, 0.1f)
{
    setShootComponent(std::make_unique<Shooter>(3000.f));
}

bool Cannon::m_registerit = Factory<PlayerSeeking>::registerit("Cannon",
    [](const char pic, const sf::Vector2f& location) -> std::unique_ptr<PlayerSeeking> { return std::make_unique<Cannon>(pic, location); });

std::unique_ptr<DynamicActives> Cannon:: updateDynamicActicve(const sf::Time& deltaTime)
{
    static int moveCounter = 0;
    static int moveDuration = 2000;

    updateAnimation(deltaTime);
    auto playerLoc = getPlayerLocation();
    moveCounter += deltaTime.asMilliseconds();

    if (m_DirectionComponent && moveCounter> moveDuration)
    {
        changeAction(Action::STANDING);
        m_DirectionComponent->doMyAlgorithm(getSprite(), playerLoc);
    }
    if (isCloseEnough(150) && m_shootComponent)
    {
        auto shoot= m_shootComponent->shoot(getSprite().getPosition(), "HeavyArtilleryBullet",getSprite().getRotation());
        if (shoot)
        {
            changeAction(Action::SHOOTIONG);
            moveCounter = 0;
        }
        return shoot;
    }
    return nullptr;
}

