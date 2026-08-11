#include "Moving.h"
#include "Marcos.h"


Moving::Moving(float speedPerSecond) :m_speedPerSecond(speedPerSecond) {}

sf::Vector2f& Moving::getBackPosition() {return m_lastPosition;}


void Moving::doMove(const sf::Time& deltaTime, sf::Sprite& sprite, sf::Vector2f& myDirection,sf::Vector2f &location)
{

    sf::Vector2f offset = myDirection * m_speedPerSecond * deltaTime.asSeconds();
    if (isWithinGameLimits(sprite.getPosition() + offset, sprite.getGlobalBounds())) {
        m_lastPosition = sprite.getPosition();
        sprite.move(offset);
        location = sprite.getPosition();
    }
}

bool Moving::isWithinGameLimits(const sf::Vector2f& position, const sf::FloatRect& bounds) const {
    return (position.x - (bounds.width/2) > padding &&
        position.y - (bounds.height/2) > padding &&
        (position.x + (bounds.width / 2)) < (screenWidth- padding) &&
        (position.y + (bounds.height / 2)) < (screenHeight- padding ));
}


float Moving::getSpeed() const {return m_speedPerSecond;}
