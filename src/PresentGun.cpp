#include "PresentGun.h"

PresentGun::PresentGun(const char pic, const sf::Vector2f& location) :StaticObject(pic, location) {}


bool PresentGun::m_registerit = Factory<StaticObject>::registerit("PresentGun",
    [](const char pic, const sf::Vector2f& location) -> std::unique_ptr<StaticObject> { return std::make_unique<PresentGun>(pic, location); });


