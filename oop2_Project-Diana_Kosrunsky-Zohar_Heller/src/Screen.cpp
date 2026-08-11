#include "Screen.h"

void Screen::run(sf::RenderWindow& window)
{
    for (auto event = sf::Event{}; window.pollEvent(event); )
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            exit(EXIT_SUCCESS);
            break;

        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
                exit(EXIT_SUCCESS);
            break;

        case sf::Event::MouseButtonReleased:
            handleMouseClick(window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }), window);
            break;

        case sf::Event::MouseMoved:
        {
            auto mouse_loc = sf::Vector2f(sf::Mouse::getPosition(window));
            handleHover(mouse_loc);
            break;
        }

        default:
            break;
        }
    }
}

void Screen::setBG(const int index)
{
    m_bg = sf::Sprite(*Resources::instance().getBackground(index));
    m_bg.setPosition(0, 0);
}
