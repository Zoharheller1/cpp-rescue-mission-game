#pragma once
#include <SFML/Graphics.hpp>
#include "StaticObject.h"
#include "Factory.h"

class PresentShild : public StaticObject
{
public:
    PresentShild(const char pic, const sf::Vector2f& location);
private:
    static bool m_registerit;

};
