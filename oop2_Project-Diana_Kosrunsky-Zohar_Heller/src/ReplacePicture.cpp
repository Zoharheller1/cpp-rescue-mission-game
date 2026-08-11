#include "ReplacePicture.h"

ReplacePicture::ReplacePicture(const char pic, const sf::Vector2f& location) :StaticObject(pic, location), m_addStaticFunc(nullptr) {}

void ReplacePicture::setAddStaticObjectFunction(std::function<void(const sf::Vector2f& position, std::string type, const char pic)> addStaticFunc)
{
    m_addStaticFunc = addStaticFunc;
}


