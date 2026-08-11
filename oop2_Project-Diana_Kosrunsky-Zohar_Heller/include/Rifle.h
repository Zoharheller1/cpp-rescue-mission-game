#include "Bullets.h"


class  Rifle :public Bullet
{
public:
	Rifle(const char pic, const sf::Vector2f& location);
private:
    static bool m_registerit;
};
