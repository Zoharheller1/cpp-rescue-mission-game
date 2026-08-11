#include "Rifle.h"
#include  "DynamicActives.h"


bool Rifle::m_registerit = Factory<Bullet>::registerit("Rifle",
    [](const char pic, const sf::Vector2f& location) -> std::unique_ptr<Bullet> { return std::make_unique<Rifle>(pic, location); });


Rifle::Rifle(const char pic, const sf::Vector2f& location) :
    Bullet(pic, location, Resources::THIRDSHOT,0.1f,350.f){}
