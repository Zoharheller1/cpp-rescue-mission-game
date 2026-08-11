#include "Bullets.h"

class Player;
class HeavyArtilleryBullet :public Bullet
{
public:
    HeavyArtilleryBullet(const char pic, const sf::Vector2f& location);
   
private:
    static bool m_registerit;
};
