#include "Caption.h"
#include "Resources.h"
#include <sstream>
#include <iomanip>
#include <iostream>


Caption::Caption(const sf::FloatRect& worldBounds, const sf::Vector2f& position) : m_worldBounds(worldBounds)
{
    m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf");

   
    m_text_caption[0] = setText("0", 40, WINDOW_WIDTH - 1330, WINDOW_HEIGHT - 710); //number Prisoners

    m_text_caption[1] = setText("0", 40, WINDOW_WIDTH - 1330, WINDOW_HEIGHT - 525); //life prsents

    m_text_caption[2] = setText("0", 40, WINDOW_WIDTH - 1330, WINDOW_HEIGHT - 770); //number Grenades

    m_text_caption[3] = setText("0", 40, WINDOW_WIDTH - 1330, WINDOW_HEIGHT - 600);// timer///////////////life prsents?
    

    m_sprite_caption[0] = setpic(Clock, WINDOW_WIDTH - 1390, WINDOW_HEIGHT - 642); // clock

    m_sprite_caption[1] = setpic(Prisionr, WINDOW_WIDTH -1390, WINDOW_HEIGHT - 735); // Prisoners

    m_sprite_caption[2] = setpic(grende, WINDOW_WIDTH - 1380, WINDOW_HEIGHT - 790); // Grenade

    m_sprite_caption[3] = setpic(battery, WINDOW_WIDTH - 1365, WINDOW_HEIGHT - 533);

    m_sprite_caption[4] = setpic(shild, WINDOW_WIDTH - 1365, WINDOW_HEIGHT - 480);

    setBatteryAnimation();
}

void Caption::draw(sf::RenderWindow& window)
{
   
    for (auto& sprite : m_sprite_caption)
    {
        window.draw(sprite);
    }

    if (m_ShildMode)window.draw(m_sprite_caption[4]);

    for (auto& texst : m_text_caption)
    {
        window.draw(texst);
    }
}

void Caption::update (float stopper,unsigned int life, unsigned int grenade, unsigned int prisioners, bool ShildMode)
{
    updateClock(stopper);
    updateInfo(life, grenade, prisioners);
    m_ShildMode = ShildMode;
}

void Caption::updateClock(float stopper)
{
   
    float minutesStopper = stopper / 60;
    float secondStopper = static_cast<int>(stopper) % 60;

    std::ostringstream timeStream;

    timeStream = fillTheString(minutesStopper, secondStopper);

    m_text_caption[3].setString(timeStream.str());

}

void Caption::setBatteryAnimation()
{
    m_animation = std::make_unique<Animation>(Resources::instance().animationData(Resources::BATTERY), Action::BLUE, m_sprite_caption[3], 0.1f);
    m_rangeOfAnimation = { { 0, 20,Action::RED },
                         { 20, 40, Action::ORANGE },
                        { 40, 60, Action::YELLOW },
                        { 60, 80, Action::GRREN },
                        { 80, 100, Action::BLUE } };
}

std::ostringstream Caption::fillTheString(int minutes, int seconds)
{
    std::ostringstream currentClock;
    currentClock << std::setfill('0') << std::setw(2) << minutes << ":" << std::setw(2) << seconds;
    return currentClock;
}

void Caption::updateInfo(unsigned int life, unsigned int grenade, unsigned int prisioners)
{
    m_text_caption[1].setString(std::to_string(life) + "%");

    m_text_caption[2].setString(std::to_string(grenade) );

    m_text_caption[0].setString(std::to_string(prisioners));

    if (life >= 100) m_animation->action(Action::BLUE);
    else for (const auto& range : m_rangeOfAnimation)
    {
        if (life >= range.lower && life < range.upper) {
            m_animation->action(range.imageName); 
            break;
        }
    }
}


sf::Sprite Caption::setpic(int wantedpic, double posX, double posY)
{
   const  sf::Texture* Pic = Resources::instance().getTexture(wantedpic);

    sf::Sprite sprite = sf::Sprite(*Pic);
    sprite.setPosition(posX, posY);

    return sprite;
}


sf::Text Caption::setText(const std::string& text, const int size, const int posX, const int posY)
{
    sf::Text textLife;
    textLife = sf::Text(text, m_font);
    textLife.setCharacterSize(size);
    textLife.setFillColor(sf::Color::Black);
    textLife.setPosition(posX, posY);
    auto textRect = textLife.getLocalBounds();
    textLife.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);

    return textLife;
}


