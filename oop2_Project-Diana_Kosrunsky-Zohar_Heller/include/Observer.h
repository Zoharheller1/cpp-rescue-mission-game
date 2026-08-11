#pragma once
#include <SFML/Graphics.hpp>
class Observer
{
public:
    virtual ~Observer() {}
    virtual void onHouseDestroyed(const sf::Vector2f& position) = 0;
};