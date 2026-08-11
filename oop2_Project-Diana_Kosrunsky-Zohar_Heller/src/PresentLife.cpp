#include "PresentLife.h"

PresentLife::PresentLife(const char pic, const sf::Vector2f& location) :StaticObject(pic, location) {}


bool PresentLife::m_registerit = Factory<StaticObject>::registerit("PresentLife",
    [](const char pic, const sf::Vector2f& location) -> std::unique_ptr<StaticObject> { return std::make_unique<PresentLife>(pic, location); });


