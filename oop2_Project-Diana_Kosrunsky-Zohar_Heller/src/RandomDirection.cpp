#include "RandomDirection.h"

void RandomDirection::doMyAlgorithm(sf::Sprite& sprite, sf::Vector2f& myDirection)
{ 
        setNewRandomDirection(sprite, myDirection); 
}


sf::Vector2f  RandomDirection::CollisionHandling(sf::Sprite& sprite, const sf::Sprite& obstacle)
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

    float angle = atan2(direction.y, direction.x);  // Base angle of reflection
    angle += (rand() % 2 == 0 ? 10 : -10) * (M_PI / 180);  // Small deviation of +/-10 degrees

    float force = std::min(20.0f, length / 2);  // Reduced force, half of the collision distance or up to 20 pixels

    direction.x = cos(angle) * force;
    direction.y = sin(angle) * force;

    return direction;
}
void RandomDirection::setNewRandomDirection(sf::Sprite& sprite, sf::Vector2f& myDirection)
{

    float angle = static_cast<float>(rand() % 360) * M_PI / 180.0f;
    myDirection = { std::cos(angle), std::sin(angle) };
    sprite.setRotation(angle * 180.0f / M_PI);
}

