#pragma once
#include <SFML/Graphics.hpp>

class AlgorithnDirection
{
public:

    virtual ~AlgorithnDirection() = default;
    virtual void doMyAlgorithm( sf::Sprite& sprite, sf::Vector2f& myDirection)=0;
    virtual sf::Vector2f CollisionHandling(sf::Sprite& sprite, const sf::Sprite& obstacle) =0;
};
