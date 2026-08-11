#pragma once
#include <SFML/Graphics.hpp>
#include "StaticObject.h"
#include "Factory.h"

class PresentLife : public StaticObject
{
public:
    PresentLife(const char pic, const sf::Vector2f& location);
private:
    static bool m_registerit;

};
