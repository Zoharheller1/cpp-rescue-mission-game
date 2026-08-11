#include "PlayerSeekingDirection.h"
#include <iostream>

void PlayerSeekingDirection::doMyAlgorithm( sf::Sprite& sprite, sf::Vector2f& playerPos)
{
    sf::Vector2f  direction = calculateDirectionTowards(playerPos, sprite.getPosition());
    sprite.setRotation(std::atan2(direction.y, direction.x) * 180.0f / M_PI);
}

sf::Vector2f  PlayerSeekingDirection::CollisionHandling(sf::Sprite& sprite, const sf::Sprite& obstacle)
{
    
    sf::FloatRect obstacleBounds = obstacle.getGlobalBounds();
    sf::FloatRect spriteBounds = sprite.getGlobalBounds();

    sf::Vector2f direction = {
        (spriteBounds.left + spriteBounds.width / 2) - (obstacleBounds.left + obstacleBounds.width / 2),
        (spriteBounds.top + spriteBounds.height / 2) - (obstacleBounds.top + obstacleBounds.height / 2)
    };

    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 0) {
        direction.x /= length;
        direction.y /= length;
    }

    float angle = atan2(direction.y, direction.x);  
    angle += (rand() % 2 == 0 ? 10 : -10) * (M_PI / 180);  

    float force = std::min(40.0f, length/2);

    direction.x = cos(angle) * force*2;
    direction.y = sin(angle) * force*2;
    return direction;
}

sf::Vector2f PlayerSeekingDirection::calculateDirectionTowards(const sf::Vector2f& target, const sf::Vector2f& current) 
{
    sf::Vector2f direction;
    float dx = target.x - current.x;
    float dy = target.y - current.y;
    float length = std::sqrt(dx * dx + dy * dy);
    if (length != 0) {
        direction = { dx / length, dy / length };
    }
    return direction;
}