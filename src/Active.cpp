#include "Active.h"

Active::Active(const char pic, const sf::Vector2f& location,const int life,Resources::Objects obj,Action act,float animationTime):
	          Object(pic, location),m_rotation(0),m_direction({ 1.f,0.f }),m_life(life)
{
	m_animation = std::make_unique<Animation>(Resources::instance().animationData(obj),act, getSprite(),animationTime);
};


void Active::setWalkComponent(std::unique_ptr<Moving> wc) {m_walkComponent = std::move(wc);}

void Active::updateLife(const float life) {m_life -= life; }

void Active::setShootComponent(std::unique_ptr<Shooter> sc) {m_shootComponent = std::move(sc);}

void Active::setDirectionComponent(std::unique_ptr<AlgorithnDirection> dc) { m_DirectionComponent = std::move(dc); }


void Active::setDirection(const sf::Vector2f direction) {m_direction = direction;}

float Active::getRotation() const{return m_rotation;}

sf::Vector2f&  Active:: getDirection() {return m_direction;}

void Active::updateAnimation(const sf::Time& deltaTime)
{
	if (m_animation) m_animation->update(deltaTime);
}

void Active::changeAction(Action act)
{
	if (m_animation) m_animation->action(act);
}


int Active::getLife() {return m_life;}

sf::Vector2f& Active::performBackPosition()
{
	if (m_walkComponent){return m_walkComponent->getBackPosition();}
}


