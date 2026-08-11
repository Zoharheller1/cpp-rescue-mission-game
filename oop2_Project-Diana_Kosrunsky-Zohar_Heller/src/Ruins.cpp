#include "Ruins.h"

Ruins::Ruins(const char pic, const sf::Vector2f& location) :StaticObject(pic, location) {}


bool Ruins::m_registerit = Factory<StaticObject>::registerit("Ruins",
    [](const char pic, const sf::Vector2f& location) -> std::unique_ptr<StaticObject> { return std::make_unique<Ruins>(pic, location); });
