#pragma once
#include"PlayerSeeking.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include "Factory.h"
//#include "Animation.h"

class Guard : public PlayerSeeking
{
public:


    Guard(const char pic, const sf::Vector2f& location);

    virtual std::unique_ptr<DynamicActives> updateDynamicActicve(const sf::Time& deltaTime) override;
    
private:
    static bool m_registerit;
};

