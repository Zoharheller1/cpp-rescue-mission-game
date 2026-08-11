#include "HeavyArtilleryBullet.h"
#include "DynamicActives.h"
#include "Player.h"

bool HeavyArtilleryBullet::m_registerit = Factory<Bullet>::registerit("HeavyArtilleryBullet",
    [](const char pic, const sf::Vector2f& location) -> std::unique_ptr<Bullet> { return std::make_unique<HeavyArtilleryBullet>(pic, location); });

HeavyArtilleryBullet::HeavyArtilleryBullet(const char pic, const sf::Vector2f& location) :
    Bullet(pic, location, Resources::FIRSTSHOT,0.1f,500.f)
{}

