#pragma once
#include "Object.h"
#include "Shooter.h"
#include "Moving.h"
#include <iostream>
#include "AlgorithnDirection.h"
#include "Animation.h"
class Player;
class Active:public  Object
{
public:

	Active(const char , const sf::Vector2f& ,const int, Resources::Objects , Action , float );
	virtual ~Active() {}

	int getLife();

    sf::Vector2f& performBackPosition() ;

protected:

	virtual void updateLife(const float life);

	void setWalkComponent(std::unique_ptr<Moving> );
	void setShootComponent(std::unique_ptr<Shooter> );
	void setDirectionComponent(std::unique_ptr<AlgorithnDirection> );
	void updateAnimation(const sf::Time& deltaTime);
	void changeAction(Action act);
	void setDirection(sf::Vector2f direction);

	std::unique_ptr<Moving> m_walkComponent;
	std::unique_ptr<AlgorithnDirection> m_DirectionComponent;
	std::unique_ptr<Shooter> m_shootComponent;

	float getRotation()const;

	sf::Vector2f & getDirection() ;

private:

	std::unique_ptr<Animation> m_animation;

	sf::Vector2f m_direction;

	float m_rotation;
	float m_life;
};
