#include"CustomClock.h"
#include <cmath>

CustomClock::CustomClock() : m_TimeLeft(300), m_startTime(300), m_timePaseed(300){}

CustomClock::CustomClock(int time) : m_TimeLeft(time), m_startTime(0), m_timePaseed(0){}

void CustomClock::bonusTime(float time)
{
    m_TimeLeft += time;

}

void CustomClock::setingTime(int time)
{
    m_TimeLeft = time;
    m_startTime = time;
    m_timePaseed = time;
}

void CustomClock::decriseTime(float time)
{
    m_TimeLeft -= time;
    m_timePaseed -= time;
}

void CustomClock::decriseTime()
{
    auto deltaTime = m_clock.getElapsedTime().asSeconds();
    m_timePaseed -= deltaTime;
    m_TimeLeft -= deltaTime;
    m_clock.restart();
}


float CustomClock::getTimeLeft()const
{
    return m_TimeLeft;
}

float CustomClock::getTimeHasPassed()const
{
    return   (abs(m_startTime - m_timePaseed));
}


void CustomClock::addingTime(float time)
{
    m_TimeLeft += time;

}

void CustomClock::addingTime()
{
    auto deltaTime = m_clock.getElapsedTime().asMilliseconds();
    m_TimeLeft += deltaTime;
    m_timePaseed += deltaTime;
    m_clock.restart();
}