#include "PlayerBullet.h"
#include "DynamicActives.h"

bool PlayerBullet::m_registerit = Factory<Bullet>::registerit("PlayerBullet",
    [](const char pic, const sf::Vector2f& location) -> std::unique_ptr<Bullet> { return std::make_unique<PlayerBullet>(pic, location); });


PlayerBullet::PlayerBullet(const char pic, const sf::Vector2f& location) :Bullet(pic, location, Resources::SECONDESHOT,0.3f,800.f){}


