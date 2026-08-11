#include "MiniMap.h"
#include<iostream>

MiniMap::MiniMap(const sf::FloatRect& worldBounds, const sf::Vector2f& size, const sf::Vector2f& position)
    : m_worldBounds(worldBounds)
{
    m_miniMap.setSize(size);
    m_miniMap.setFillColor(sf::Color(50, 50, 50, 200));
    m_miniMap.setPosition(position);

    m_playerMarker.setRadius(5);
    m_playerMarker.setFillColor(sf::Color::Green);

    m_destinationMarker.setRadius(5);
    m_destinationMarker.setFillColor(sf::Color::Red);
}

void MiniMap::update(const sf::Vector2f& playerPosition)
{
    m_playerMarker.setPosition(worldToMiniMap(playerPosition));
}

void MiniMap::draw(sf::RenderWindow& window)
{
    window.draw(m_miniMap);
    window.draw(m_destinationMarker);

    for (const auto& houseMarker : m_houseMarkers) {
        window.draw(houseMarker);
    }
    window.draw(m_playerMarker);
}

void MiniMap::setDestination(const sf::Vector2f& destination)
{
    sf::Vector2f miniMapPos = m_miniMap.getPosition();
    sf::Vector2f miniMapSize = m_miniMap.getSize();
    sf::Vector2f miniMapCoord = worldToMiniMap(destination);

    if (miniMapCoord.x < miniMapPos.x) miniMapCoord.x = miniMapPos.x;
    if (miniMapCoord.x > miniMapPos.x + miniMapSize.x) miniMapCoord.x = miniMapPos.x + miniMapSize.x;
    if (miniMapCoord.y < miniMapPos.y) miniMapCoord.y = miniMapPos.y;
    if (miniMapCoord.y > miniMapPos.y + miniMapSize.y) miniMapCoord.y = miniMapPos.y + miniMapSize.y;

    m_destinationMarker.setPosition(miniMapCoord);
}

void MiniMap::addHouse(const sf::Vector2f& position)
{
    sf::CircleShape houseMarker(5);
    houseMarker.setFillColor(sf::Color::Blue);
    houseMarker.setPosition(worldToMiniMap(position));

    m_houseMarkers.push_back(houseMarker);
}


sf::Vector2f MiniMap::worldToMiniMap(const sf::Vector2f& position)
{
    sf::Vector2f miniMapPos = m_miniMap.getPosition();
    sf::Vector2f miniMapSize = m_miniMap.getSize();


    sf::Vector2f relativePos = {
        ((position.x - m_worldBounds.left) / m_worldBounds.width) * miniMapSize.x,
        ((position.y - m_worldBounds.top) / m_worldBounds.height) * miniMapSize.y
    };

    sf::Vector2f miniMapCoord = miniMapPos + relativePos;

    if (miniMapCoord.x < miniMapPos.x) miniMapCoord.x = miniMapPos.x;
    if (miniMapCoord.x > miniMapPos.x + miniMapSize.x) miniMapCoord.x = miniMapPos.x + miniMapSize.x;
    if (miniMapCoord.y < miniMapPos.y) miniMapCoord.y = miniMapPos.y;
    if (miniMapCoord.y > miniMapPos.y + miniMapSize.y) miniMapCoord.y = miniMapPos.y + miniMapSize.y;

    return miniMapCoord;
}

sf::Vector2f MiniMap::miniMapToWorld(const sf::Vector2f& miniMapCoord)
{
    sf::Vector2f miniMapPos = m_miniMap.getPosition();
    sf::Vector2f miniMapSize = m_miniMap.getSize();
    sf::Vector2f relativePos = {
        (miniMapCoord.x - miniMapPos.x) / miniMapSize.x,
        (miniMapCoord.y - miniMapPos.y) / miniMapSize.y
    };
    sf::Vector2f worldPos = {
        m_worldBounds.left + (relativePos.x * m_worldBounds.width),
        m_worldBounds.top + (relativePos.y * m_worldBounds.height)
    };

    return worldPos;
}

void MiniMap::deleteAllHouses() {m_houseMarkers.clear();}


void MiniMap::onHouseDestroyed(const sf::Vector2f& position)
{
    removeHouse(position);

}

void MiniMap::removeHouse(const sf::Vector2f& position)
{
    auto it = std::remove_if(m_houseMarkers.begin(), m_houseMarkers.end(),
        [&position, this](const sf::CircleShape& marker)
        {
            auto  realPos = miniMapToWorld(marker.getPosition());

            return ((std::abs(realPos.x - position.x) < 5.f) && (std::abs(realPos.y - position.y) < 5.f));

        });
    if (it != m_houseMarkers.end())
    {
        m_houseMarkers.erase(it, m_houseMarkers.end());
    }
}

