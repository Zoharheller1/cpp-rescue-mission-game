#pragma once
#include "Bullets.h"
#include <SFML/Graphics.hpp>
#include "Factory.h"

class Grende :public Bullet
{
public:
 
    Grende(const char pic, const sf::Vector2f& location);
    virtual  std::unique_ptr<DynamicActives> updateDynamicActicve(const sf::Time& deltaTime) override;

  
private:
    static bool m_registerit;
   
};
