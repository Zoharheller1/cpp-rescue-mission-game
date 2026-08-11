#pragma once
#include "AlgorithnDirection.h"
#include <cstdlib> 
#include <cmath>    
#include "Marcos.h"

class RandomDirection : public AlgorithnDirection
{
public:
    virtual  void   doMyAlgorithm( sf::Sprite& sprite, sf::Vector2f& myDirection)override;
    sf::Vector2f  CollisionHandling(sf::Sprite& sprite, const sf::Sprite& obstacle);
private:
    void setNewRandomDirection(sf::Sprite& sprite, sf::Vector2f& myDirection);
};
