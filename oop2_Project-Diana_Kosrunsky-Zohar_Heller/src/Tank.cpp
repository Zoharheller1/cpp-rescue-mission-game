#include"Tank.h"



Tank::Tank(const char pic, const sf::Vector2f& location) : PlayerSeeking(pic, location,35, Resources::TANK, Action::WALKING, 0.1f)
{ 
    setWalkComponent(std::make_unique<Moving>(45.f));
    setShootComponent(std::make_unique<Shooter>(1500.f));
}

bool Tank::m_registerit = Factory<PlayerSeeking>::registerit("Tank",
    [](const char pic, const sf::Vector2f& location) -> std::unique_ptr<PlayerSeeking> { return std::make_unique<Tank>(pic, location); });



std::unique_ptr<DynamicActives> Tank::updateDynamicActicve(const sf::Time& deltaTime)
{
	
    static int moveCounter = 0;
    static int moveDuration = 2000;
    moveCounter += deltaTime.asMilliseconds();
    if (isCloseEnough(200) && m_shootComponent && m_walkComponent)
    {
        updateAnimation(deltaTime);

        auto playerLoc = getPlayerLocation();
        if (m_DirectionComponent && moveCounter >= moveDuration)
        {
            changeAction(Action::WALKING);
            m_DirectionComponent->doMyAlgorithm(getSprite(), playerLoc);

            setDirection({ std::cosf(getSprite().getRotation() * M_PI / 180.0f), std::sinf(getSprite().getRotation() * M_PI / 180.0f) });
            m_walkComponent->doMove(deltaTime, getSprite(), getDirection(), getLocation());
        }
        float barrelLength = 50.0f,
              angle = getSprite().getRotation(); 

        sf::Vector2f barrelEndOffset(cos(angle * M_PI / 180) * barrelLength, sin(angle * M_PI / 180) * barrelLength),
                     bulletStartPosition = getSprite().getPosition() + barrelEndOffset;

        auto shoot= m_shootComponent->shoot(bulletStartPosition, "HeavyArtilleryBullet", angle);
        if (shoot)
        {
            changeAction(Action::SHOOTIONG);
            moveCounter = 0;
            return shoot;
        }
    }
    return nullptr;
}


