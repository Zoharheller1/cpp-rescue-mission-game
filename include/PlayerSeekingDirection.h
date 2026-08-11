#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Marcos.h"
#include "AlgorithnDirection.h"

class PlayerSeekingDirection : public AlgorithnDirection
{
public:
    virtual void doMyAlgorithm( sf::Sprite& sprite, sf::Vector2f& playerPos) override;
    virtual sf::Vector2f CollisionHandling(sf::Sprite& sprite, const sf::Sprite& obstacle) override;
private:
    sf::Vector2f calculateDirectionTowards(const sf::Vector2f& target, const sf::Vector2f& current);
};



