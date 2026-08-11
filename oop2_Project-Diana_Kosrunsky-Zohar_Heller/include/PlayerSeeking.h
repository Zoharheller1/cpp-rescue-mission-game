#pragma once
#include"DynamicActives.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include "Factory.h"
#include "PlayerSeekingDirection.h"

class PlayerSeeking : public DynamicActives
{
public:
 
    PlayerSeeking(const char , const sf::Vector2f& ,const int,Resources::Objects , Action , float );
    virtual ~PlayerSeeking() = default;

    virtual void updatePlayerLocation(const sf::Vector2f& place);
     
    const sf::Vector2f  getPlayerLocation()const ;

    bool isCloseEnough(const int)const;

private:

    sf::Vector2f m_playerLocation = {0,0};
};




    