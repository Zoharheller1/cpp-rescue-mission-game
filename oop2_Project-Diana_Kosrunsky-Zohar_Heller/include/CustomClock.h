#pragma once
#include <SFML/System/Clock.hpp>

class CustomClock
{
public:

    CustomClock();

    CustomClock(int);

    float getTimeLeft()const;

    float getTimeHasPassed()const;

    void addingTime();
    void addingTime(float time);



    void setingTime(int time);

    void decriseTime();

    void decriseTime(float time);

    void bonusTime(float);

private:

    sf::Clock m_clock;
    float m_timePaseed;
    float m_TimeLeft;
    float m_startTime;
};