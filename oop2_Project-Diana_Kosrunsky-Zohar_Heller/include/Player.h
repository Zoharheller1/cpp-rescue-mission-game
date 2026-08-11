#pragma once
#include"Active.h"
#include "CustomClock.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include "PlayerSeeking.h"

class Player : public Active
{

public:

    Player(CustomClock& clock, const char pic, const sf::Vector2f& location);
    ~Player();

    virtual void updateLife(const float life)override;
 
    void attach(PlayerSeeking* obs);
    void detach();
    void notify();
    void addPrisioner();
    void addGrendes();
    void setSituation(const float);
    void updateSituation(const sf::Time& deltaTime);
    void addTime();
    void addLife();
    void performWalk(const sf::Time& deltaTime, const  sf::Vector2f& direction);
    void returnBack(const Object& object);
    void ShildBegin();
    void spotPosition();
    void setMakeSoundFunction(const std::function<void(int)>& makeSoundFunc);


    void endGameFunction(std::function<void(const std::string& songName, int picture)> winMatch);
    bool getIsAttacked();
    bool getShildMode()const;

    unsigned int getGrenadesAmount()const;
    unsigned int getPrisionerAmount()const;

    float getSpeedPlayer()const;
   
    sf::Vector2f getPos() const;

    std::unique_ptr<DynamicActives> shoot(const sf::Time& deltaTime);
    std::vector<std::unique_ptr<DynamicActives>> shootGrenade(const sf::Time& deltaTime);


private:

    void bonusSound();

    bool m_isAttacked = false;
    bool m_shildMode = false;

    float m_endingAttack = 0.f;
    float m_grendeTime = 0.f;
    float m_stoperShild = 0.f;

    unsigned int m_prisioner = 0;
    unsigned int m_grende = 2;

    std::function<void(const std::string& songName, int picture)> m_endMatch;

    CustomClock& m_clock;

    std::function<void(int)> m_makeSoundFunc;

    std::vector<PlayerSeeking*> observers;
};