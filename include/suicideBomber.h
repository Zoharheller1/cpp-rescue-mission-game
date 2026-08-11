#pragma once
#include "PlayerSeeking.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include "Factory.h"
#include "Player.h"
class suicideBomber : public PlayerSeeking
{
public:

    suicideBomber(const char pic, const sf::Vector2f& location);
    virtual  std::unique_ptr<DynamicActives> updateDynamicActicve(const sf::Time& deltaTime) override;
    bool collisionWithPlayer();

private:
    sf::Time m_delta;
    float m_speed = 3;
    static bool m_registerit;
    sf::Vector2f m_secondeDirection;
};

