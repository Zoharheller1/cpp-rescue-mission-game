#pragma once
#include <SFML/Graphics.hpp>

class Moving 
{
public:
  
    Moving(float speedPerSecond);
    virtual ~Moving() = default;
    void doMove(const sf::Time& deltaTime, sf::Sprite& sprite, sf::Vector2f& myDirection, sf::Vector2f& location);
    bool isWithinGameLimits(const sf::Vector2f& position, const sf::FloatRect& bounds) const; 
    float getSpeed() const;
    sf::Vector2f& getBackPosition();

protected:

    float m_speedPerSecond=10.f;
    static constexpr float screenWidth = 2560.f;
    static constexpr float screenHeight = 5000.0f;
    static constexpr float padding = 5.f;

private: 
    sf::Vector2f m_lastPosition; 
};

