#pragma once
#include "Action.h"
#include "AnimationData.h"
#include <SFML/Graphics.hpp>

class Animation
{
public:

    Animation(const AnimationData& data, Action dir, sf::Sprite& sprite, float Timer);
    void update(sf::Time delta);
    void action(Action dir);

private:

    void update();

    const AnimationData& m_data;
   
    Action m_dir = Action::WALKING;

    int m_index;

    sf::Time m_elapsed = {};
    sf::Sprite& m_sprite;
    sf::Time m_animationTime;
};