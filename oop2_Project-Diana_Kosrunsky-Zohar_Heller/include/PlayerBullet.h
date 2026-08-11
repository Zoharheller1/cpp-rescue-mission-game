#pragma once
#include "Bullets.h"
#include <SFML/Graphics.hpp>
#include "Factory.h"

class PlayerBullet :public Bullet
{
public:

    PlayerBullet(const char pic, const sf::Vector2f& location);
   
private:
   
    static bool m_registerit;
};
