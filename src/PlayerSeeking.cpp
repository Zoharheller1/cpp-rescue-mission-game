#include "PlayerSeeking.h"


PlayerSeeking::PlayerSeeking(const char pic, const sf::Vector2f& location,const int life,Resources::Objects obj, Action act, float animationTime) :DynamicActives(pic, location,life,obj,act, animationTime)
{
    setDirectionComponent(std::make_unique<PlayerSeekingDirection>());
};

void PlayerSeeking::updatePlayerLocation(const sf::Vector2f& place) {m_playerLocation = place;}


const sf::Vector2f PlayerSeeking:: getPlayerLocation()const {return m_playerLocation; }


bool PlayerSeeking::isCloseEnough(const int limit)const
{
	sf::Vector2f myPlace = getSprite().getPosition();
	return (abs(myPlace.x - m_playerLocation.x) + abs(myPlace.y - m_playerLocation.y) < 2000.f);
}
