#include "Shooter.h"
#include "Bullets.h"
#include "DynamicActives.h"
Shooter::Shooter(float distanceTime):m_distanceTime(distanceTime),m_clock(1){}

std::unique_ptr<DynamicActives> Shooter::shoot(const sf::Vector2f& position, std::string type, float rotation)
{
    m_clock.addingTime();
    if (m_clock.getTimeHasPassed() > m_distanceTime || type == "Grende")
    {
        m_clock.setingTime(0);
        auto myBullet = Factory<Bullet>::create(type, AnimationPic, position);
        if(myBullet)
            myBullet->setRotation(rotation);
        return myBullet;
    }
    return nullptr;
}




