#include "Gate.h"

Gate::Gate(const char pic, const sf::Vector2f& location) :ReplacePicture(pic, location) {}

void Gate::handleCollisionWithBullet()
{
    if (isAlive())
    {
        deadObject();
        if (m_addStaticFunc)
        {
            m_addStaticFunc(getSprite().getPosition(), "Ruins", smallRuined);
        }
    }
}

bool Gate::m_registerit = Factory<ReplacePicture>::registerit("Gate",
    [](const char pic, const sf::Vector2f& location) -> std::unique_ptr<ReplacePicture> { return std::make_unique<Gate>(pic, location); });

