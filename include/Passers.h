#pragma once
#include"DynamicActives.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include "Factory.h"
#include "RandomDirection.h"
class Passers : public DynamicActives
{
public:
    Passers(const char pic, const sf::Vector2f& location);
    virtual  std::unique_ptr<DynamicActives> updateDynamicActicve(const sf::Time& deltaTime) override;
private:
    static bool m_registerit;
};


