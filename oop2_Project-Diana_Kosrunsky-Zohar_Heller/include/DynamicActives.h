#pragma once
#include "Active.h"
#include <iostream>

class DynamicActives :public Active
{
public:

    DynamicActives(const char pic, const sf::Vector2f& location,const int life,Resources::Objects obj, Action act, float speed);
    ~DynamicActives() = default;
   
    bool collision(const float, const int);
    bool deleteObj()const;
    virtual std::unique_ptr<DynamicActives> updateDynamicActicve(const sf::Time& deltaTime) = 0;
  
    void returnBack(const Object& object);

protected:

    void setKillTime(const float);
    void addDeadTime(sf::Time const deltaTime);

private:
    float m_timerDead = 0.f;
    float m_whenToKill = 0.1f;
};



