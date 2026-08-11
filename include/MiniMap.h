#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include "Observer.h"
class MiniMap : public Observer
{
public:

    MiniMap(const sf::FloatRect& worldBounds, const sf::Vector2f& size, const sf::Vector2f& position);

    void update(const sf::Vector2f& playerPosition);
    void onHouseDestroyed(const sf::Vector2f& position) override;
    void draw(sf::RenderWindow& window);
    void setDestination(const sf::Vector2f& destination);
    void addHouse(const sf::Vector2f& position);
    void deleteAllHouses();

private:

    sf::Vector2f worldToMiniMap(const sf::Vector2f& position);
    sf::Vector2f miniMapToWorld(const sf::Vector2f& miniMapCoord);

    sf::RectangleShape m_miniMap;
    sf::CircleShape m_playerMarker;
    sf::CircleShape m_destinationMarker;
    std::vector<sf::CircleShape> m_houseMarkers;
    sf::FloatRect m_worldBounds;
    void removeHouse(const sf::Vector2f& position);
};


