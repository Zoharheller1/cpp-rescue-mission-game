#pragma once
#include "DynamicActives.h"
#include <memory>
#include "RandomDirection.h"
#include <SFML/Graphics.hpp>
#include "Factory.h"

class Prisioner : public DynamicActives
{
public:

 

    Prisioner(const char pic, const sf::Vector2f& location);//

    virtual  std::unique_ptr<DynamicActives> updateDynamicActicve(const sf::Time& deltaTime)override;
private:
    int moveCounter = 0;
    static bool m_registerit;
};

