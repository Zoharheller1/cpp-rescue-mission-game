#include "House.h"

House::House(const char pic, const sf::Vector2f& location) :ReplacePicture(pic, location) {}

void House::handleCollisionWithBullet()
{
    if (isAlive())
    {
        deadObject();
        notifyObservers();
        detachObserver();
        if (m_addStaticFunc)m_addStaticFunc(getSprite().getPosition(), "Ruins", Ruined);
    }
}


void House::detachObserver(){observer = nullptr;}

void  House::attachObserver(Observer* obs){observer = obs;}

void House::notifyObservers()
{
    if (observer) {observer->onHouseDestroyed(getLocation());}
}