#include "Animation.h"
#include <iostream>

//const auto AnimationTime = sf::seconds(0.1f);
Animation::Animation(const AnimationData& data, Action dir, sf::Sprite& sprite, float timer)
    :m_data(data), m_dir(dir), m_sprite(sprite), m_animationTime(sf::seconds(timer)),m_index(0)
{
    update();
}

void Animation::update()
{
    auto rect = m_data.m_data.find(m_dir)->second[m_index];
    sf::Vector2f currentPosition = m_sprite.getPosition();
    m_sprite.setTextureRect(rect);
    float centerX = rect.width / 2.0f;
    float centerY = rect.height / 2.0f;
    m_sprite.setOrigin(centerX, centerY);
    m_sprite.setPosition(currentPosition);
}

void Animation::action(Action dir)
{
    if (m_dir == dir) return;

    m_dir = dir;
    m_index = 0;
    update();
}
void Animation::update(sf::Time delta)
{
    m_elapsed += delta;
    if (m_elapsed >= m_animationTime || m_elapsed  < sf::Time::Zero)
    {
        m_elapsed -= m_animationTime;
        ++m_index;
        m_index %= m_data.m_data.find(m_dir)->second.size();

        update();
    }
}

