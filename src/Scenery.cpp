#include "Scenery.h"

Scenery::Scenery(const char pic,const sf::Vector2f& location):StaticObject(pic,location){}

bool Scenery::m_registerit = Factory<StaticObject>::registerit("Scenery",
    [](const char pic, const sf::Vector2f& location) -> std::unique_ptr<StaticObject> { return std::make_unique<Scenery>(pic, location); });
