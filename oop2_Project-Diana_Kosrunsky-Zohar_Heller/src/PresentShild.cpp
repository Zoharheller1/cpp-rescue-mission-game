#include "PresentShild.h"

PresentShild::PresentShild(const char pic, const sf::Vector2f& location) :StaticObject(pic, location) {}

bool PresentShild::m_registerit = Factory<StaticObject>::registerit("PresentShild",
    [](const char pic, const sf::Vector2f& location) -> std::unique_ptr<StaticObject> { return std::make_unique<PresentShild>(pic, location); });


