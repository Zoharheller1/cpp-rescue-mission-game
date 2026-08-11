#include "Object.h"

Object::Object(const sf::Texture& texture, const sf::Vector2f& location)
    : m_sprite(texture), m_location(location)
{
    setSpriteLocation(location);
}

Object::Object(const char  pic, const sf::Vector2f& location):m_toDeleat(false)
{
    m_sprite.setTexture(*Resources::instance().getTexture(pic));
    setSpriteLocation(location);
}
void Object::setSpriteLocation(const sf::Vector2f& location)
{
  
    m_sprite.setPosition(location);
    m_location = location;
    auto spriteRect = m_sprite.getLocalBounds();
    float centerX = spriteRect.left + spriteRect.width / 2.0f;
    float centerY = spriteRect.top + spriteRect.height / 2.0f;
    m_sprite.setOrigin(centerX, centerY);
}


void Object::deadObject(){ m_toDeleat = true; }

bool Object::isAlive()const { return !m_toDeleat; }

void Object::draw(sf::RenderWindow& window) const { window.draw(m_sprite); }

sf::Vector2f Object::getPosition()const { return m_location; }

sf::Vector2f& Object::getLocation() { return m_location; }


sf::Sprite& Object::getSprite() {return m_sprite;}


sf::Sprite Object::getSprite() const {return m_sprite;}

bool Object::checkCollision(const Object& other)const
{
    if (&other == this) return false;
    return (m_sprite.getGlobalBounds().intersects(other.getSprite().getGlobalBounds()));
}

void Object::SetLocation(const sf::Vector2f& newLocation)
{
    m_location = newLocation;
    m_sprite.setPosition(newLocation);
}