#pragma once
#include "DynamicActives.h"
#include <SFML/Graphics.hpp>
#include "Marcos.h"
#include "CustomClock.h"
#include "Factory.h"


class Bullet :public DynamicActives
{
public:

    Bullet(const char pic, const sf::Vector2f&, Resources::Objects ,const float ,const float);//
    virtual ~Bullet() = default;

    virtual  std::unique_ptr<DynamicActives> updateDynamicActicve(const sf::Time& ) override;

    void setRotation( float);

    bool overBoard()const;
    bool colide(const sf::Vector2f ,const Action ,const float);
   
protected:
    bool endTime()const;

private:

    void updateTime();
    void toBomber(Action);

    static bool m_registerit;
    CustomClock m_clock;

};
