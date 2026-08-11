#include "DynamicActives.h"

DynamicActives::DynamicActives(const char pic, const sf::Vector2f& location,const int life,Resources::Objects obj, Action act, float animationTime):Active(pic,location,life,obj,act, animationTime){}

void DynamicActives::setKillTime(const float whenToKill) { if (whenToKill > -1) m_whenToKill = whenToKill; }

bool DynamicActives::deleteObj()const {return m_timerDead >= m_whenToKill;}

bool DynamicActives::collision(const float killTime,const int life)
{
    updateLife(life);
    if (isAlive() && getLife() <= 0)
    {
        setKillTime(killTime);
        deadObject(); 
        return true;
    }
    return false;
}

void DynamicActives::returnBack(const Object& object)
{
    if (m_walkComponent && m_DirectionComponent)
    {
        sf::Vector2f direction = m_DirectionComponent->CollisionHandling(getSprite(), object.getSprite());
        sf::Vector2f newPosition = getSprite().getPosition() + direction;

        float spriteWidth = getSprite().getGlobalBounds().width;
        float spriteHeight = getSprite().getGlobalBounds().height;
        
        if (!m_walkComponent->isWithinGameLimits(newPosition, getSprite().getGlobalBounds()))
        {
            if (newPosition.x - (spriteWidth / 2) < 5.0f || newPosition.x + (spriteWidth / 2) > 2560.0f - 5.0f) {
                direction.x = -direction.x; 
            }
            else if(newPosition.y - (spriteHeight / 2) < 5.0f || newPosition.y + (spriteHeight / 2) > 5000.0f - 5.0f) 
            {
                direction.y = -direction.y;  
            }
        }
        getSprite().setPosition(getSprite().getPosition().x + direction.x, getSprite().getPosition().y + direction.y);
        SetLocation(getSprite().getPosition());
    }    
}




void DynamicActives::addDeadTime(sf::Time const deltaTime){ m_timerDead += deltaTime.asSeconds(); }









