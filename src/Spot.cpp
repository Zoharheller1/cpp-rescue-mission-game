#include "Spot.h"

Spot::Spot(const char pic, const sf::Vector2f& location) :StaticObject(pic, location) {}

bool Spot::m_registerit = Factory<StaticObject>::registerit("Spot",
    [](const char pic, const sf::Vector2f& location) -> std::unique_ptr<StaticObject> { return std::make_unique<Spot>(pic, location); });
