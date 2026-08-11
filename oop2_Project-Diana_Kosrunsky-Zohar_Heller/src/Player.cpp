#include"Player.h"
#include "DynamicActives.h"
#include <array>

Player::Player(CustomClock& clock, const char pic, const sf::Vector2f& location) : Active(pic, location, 100, Resources::PLAYER, Action::WALKING, 0.01f), m_clock(clock)
{
    setWalkComponent(std::make_unique<Moving>(350.f));
    setShootComponent(std::make_unique<Shooter>(200.f));
}


void Player::updateLife(const float life)
{
    if (!m_shildMode)  
        Active::updateLife(life);
    if (getLife() <= 0.f)  
        m_endMatch("loseEnd.wav", 0);
}


void Player::setMakeSoundFunction(const std::function<void(int)>& makeSoundFunc)
{
    m_makeSoundFunc = makeSoundFunc;
}

Player::~Player() {}

void Player::ShildBegin()
{
    bonusSound();
    m_shildMode = true;
    getSprite().setColor(sf::Color::Green);
    m_stoperShild = (rand() % 5 + 2.f);
}

void Player::addGrendes() {m_grende += ((rand() % 3) + 1);}

void Player::spotPosition()
{
    if (m_prisioner == 3 && m_endMatch)
        m_endMatch("winSong.wav", 1);
}


void Player::endGameFunction(std::function<void(const std::string& songName, int picture)> winFunc)
{
    m_endMatch = winFunc;
}


std::unique_ptr<DynamicActives> Player::shoot(const sf::Time& deltaTime)
{
    if (m_shootComponent)
    {
        auto  Bullet = m_shootComponent->shoot(getSprite().getPosition(), "PlayerBullet", getSprite().getRotation());
        if (Bullet && m_makeSoundFunc)
        {
            m_makeSoundFunc(int(SoundManager::Sounds::SHOOT));
        }
        return  Bullet;
    }
    return nullptr;
}
std::vector<std::unique_ptr<DynamicActives>> Player::shootGrenade(const sf::Time& deltaTime)
{
    std::vector<std::unique_ptr<DynamicActives>> grenades;


    if (m_shootComponent && m_grende > 0&& m_grendeTime > 1.f)
    {

        std::array<float, 4> angles = { 90.0f, 180.0f, 270.0f, 0.0f };
        for (auto angle : angles)
        {
            auto grenadePtr = m_shootComponent->shoot(getSprite().getPosition(), "Grende", angle);
            if (grenadePtr)
            {
                grenades.push_back(std::move(grenadePtr));
            }
        }

        if (!grenades.empty())
        {
            m_grendeTime = 0.f;

            if (m_makeSoundFunc)
            {
                m_makeSoundFunc(int(SoundManager::Sounds::GRENDE));
            }
            m_grende--;
        }
    }

    return grenades;
}


unsigned int  Player::getGrenadesAmount()const
{
    return m_grende;
}
unsigned int  Player::getPrisionerAmount()const
{
    return m_prisioner;
}

void Player::addPrisioner()
{
    m_prisioner++;

    if (m_makeSoundFunc)
    {
        m_makeSoundFunc(int(SoundManager::Sounds::PRISIONER));
    }

    updateAnimation(sf::seconds(-1.0f));
}

void Player::setSituation(const float whanToEnd)
{
    m_isAttacked = true;
    m_endingAttack = whanToEnd;
}
void Player::updateSituation(const sf::Time& deltaTime)
{
    if (m_isAttacked)
    {
        m_endingAttack -= deltaTime.asSeconds();
        if (m_endingAttack <= 0)
        {
            m_endingAttack = 0.f;
            m_isAttacked = false;
        }
    }
    if (m_shildMode)
    {
        m_stoperShild -= deltaTime.asSeconds();
        if (m_stoperShild <= 0.f)
        {
            m_shildMode = false;
            getSprite().setColor(sf::Color(255, 255, 255, 255));
        }
    }
    m_grendeTime += deltaTime.asSeconds();
}

bool Player::getShildMode()const
{
    return m_shildMode;
}

void Player::addTime()
{
    bonusSound();
    m_clock.addingTime(rand() % 20);
}

void Player::addLife()
{
    bonusSound();
    updateLife(- (rand() %5)-4 );
}


void Player::bonusSound()
{
    if (m_makeSoundFunc) {m_makeSoundFunc(int(SoundManager::Sounds::BONUS));}
}


bool Player::getIsAttacked() { return m_isAttacked; }

sf::Vector2f Player::getPos() const
{
    return getSprite().getPosition();
}

void Player::attach(PlayerSeeking* obs) { observers.push_back(obs); }

void Player::detach()
{
    observers.erase(std::remove_if(observers.begin(), observers.end(), [](PlayerSeeking* obs)
        {return !obs->isAlive(); }), observers.end());
}


float Player::getSpeedPlayer()const
{
    return m_walkComponent->getSpeed();
}

void Player::notify()
{
    for (PlayerSeeking* obs : observers)
    {
        obs->updatePlayerLocation(getSprite().getPosition());
    }
}

void Player::performWalk(const sf::Time& deltaTime, const sf::Vector2f& direction)
{
    setDirection(direction);
    sf::Vector2f location = getSprite().getPosition();

    float angleRadians = std::atan2(direction.y, direction.x);

    float angleDegrees = ((angleRadians * 180.0f / M_PI));

    getSprite().setRotation(angleDegrees);

    m_walkComponent->doMove(deltaTime, getSprite(), getDirection(), getLocation());

}


void Player::returnBack(const Object& object)
{
    sf::FloatRect obstacleBounds = object.getSprite().getGlobalBounds();

    sf::Vector2f direction = {
        (getSprite().getGlobalBounds().left + getSprite().getGlobalBounds().width / 2) - (obstacleBounds.left + obstacleBounds.width / 2),
        (getSprite().getGlobalBounds().top + getSprite().getGlobalBounds().height / 2) - (obstacleBounds.top + obstacleBounds.height / 2)
    };

    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    direction.x /= length;
    direction.y /= length;

    float angle = atan2(direction.y, direction.x) + 30 * (M_PI / 180);
    direction.x = cos(angle) * 50.0;
    direction.y = sin(angle) * 50.0;

    getSprite().setPosition(getSprite().getPosition().x + direction.x, getSprite().getPosition().y + direction.y);
}