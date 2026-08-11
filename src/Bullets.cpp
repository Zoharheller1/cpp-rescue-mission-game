#include "Bullets.h"



Bullet::Bullet(const char pic, const sf::Vector2f& location, Resources::Objects obj,const float animationTime,const float speedBullet) :m_clock(2), DynamicActives(pic, location, 1, obj, Action::WALKING, animationTime)
{
	setWalkComponent(std::make_unique<Moving>(speedBullet));
}

bool Bullet::overBoard()const
{
	return (getPosition().x < 50 || getPosition().x >2510 || getPosition().y < 50 || getPosition().y >4950);
}

bool Bullet::endTime()const { return (m_clock.getTimeLeft() <= 0.f); }

void Bullet::updateTime() { m_clock.decriseTime(); }

void Bullet::toBomber(Action act) { changeAction(act); }

void Bullet::setRotation( float rotation)
{
	getSprite().setRotation(rotation);
	setDirection({ std::cosf(getSprite().getRotation() * M_PI / 180.0f), std::sinf(getSprite().getRotation() * M_PI / 180.0f) });
}


std::unique_ptr<DynamicActives> Bullet::updateDynamicActicve(const sf::Time& deltaTime)
{
	
	updateAnimation(deltaTime);
	if (m_walkComponent && isAlive())  m_walkComponent->doMove(deltaTime, getSprite(), getDirection(), getLocation());
	
	if (!isAlive()) addDeadTime(deltaTime);

	else if (endTime() || overBoard())
	{
		deadObject();
		setKillTime(0.f);
	}
	
	updateTime();
	return nullptr;
}

bool Bullet::colide(const sf::Vector2f location,const Action act,const float killTime)
{
	if (DynamicActives::collision(killTime,1))
	{
		setSpriteLocation(location);
		setRotation(0);
		toBomber(act);
		return true;
	}
	return false;
}
