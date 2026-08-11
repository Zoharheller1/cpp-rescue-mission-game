#pragma once
#include <SFML/Graphics.hpp>
#include "PlayerSeeking.h"
#include "Factory.h"
//#include "Animation.h"

class Helicopter : public PlayerSeeking
{
public:
    Helicopter(const char pic, const sf::Vector2f& location);
    void setAddStaticObjectFunction(std::function<void(const sf::Vector2f& position, std::string type, const char pic)> addStaticFunc);
    virtual std::unique_ptr<DynamicActives> updateDynamicActicve(const sf::Time& deltaTime) override;
    void createSpot();
private:
  
    static bool m_registerit;
    std::function<void(const sf::Vector2f& position, std::string type, const char pic)> m_addStaticFunc;
};