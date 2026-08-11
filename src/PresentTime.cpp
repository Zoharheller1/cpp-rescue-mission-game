#include "PresentTime.h"

PresentTime::PresentTime(const char pic, const sf::Vector2f& location) :StaticObject(pic, location) {}


bool PresentTime::m_registerit = Factory<StaticObject>::registerit("PresentTime",
    [](const char pic, const sf::Vector2f& location) -> std::unique_ptr<StaticObject> { return std::make_unique<PresentTime>(pic, location); });


