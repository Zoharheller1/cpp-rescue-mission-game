#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "CustomClock.h"
#include "Animation.h"


class gamePlay;

class Caption
{
public:

    Caption(const sf::FloatRect& worldBounds, const sf::Vector2f& position);
   
    void draw(sf::RenderWindow&);

    void update(float, unsigned int, unsigned int, unsigned int, bool);

private:

    struct Range {
        int lower,
            upper;
        Action imageName;
    };

    void updateInfo(unsigned int , unsigned int , unsigned int );

    void updateClock(float stoper);

    void setBatteryAnimation();

    sf::FloatRect m_worldBounds;

    sf::Text setText(const std::string&, const int, const int, const int);

    sf::Sprite setpic(int, double, double);

    std::ostringstream fillTheString(int, int);

    std::vector<sf::Sprite> m_prisioners;

    sf::Sprite m_sprite_caption[5];

    sf::Text m_text_caption[4];

    bool m_ShildMode = false;

    sf::Font m_font;

    std::vector<Range> m_rangeOfAnimation;

    std::unique_ptr<Animation> m_animation;
};
