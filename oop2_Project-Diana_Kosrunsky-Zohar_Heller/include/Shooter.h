#pragma once
#include <cstdlib>
#include "Factory.h"
#include "CustomClock.h"

class DynamicActives;
class Shooter
{
public:
   
    Shooter( float distanceTime);
    ~Shooter() = default;
    std::unique_ptr<DynamicActives> shoot(const sf::Vector2f& position, std::string, float rotation);
private:
    CustomClock  m_clock ;
    float m_distanceTime ;
};
