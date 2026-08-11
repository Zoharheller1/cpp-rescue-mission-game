#include "GamePlay.h"
#include <iostream>

GamePlay::GamePlay(Controller* controller) : Screen(controller),
worldBounds(0.f, 0.f, 2560, 5000), m_view(sf::FloatRect(0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT))
{
    float aspectRatio = worldBounds.width / worldBounds.height;
    float miniMapHeight = 150;
    float miniMapWidth = miniMapHeight * aspectRatio;
    m_miniMap = std::make_unique<MiniMap>(worldBounds, sf::Vector2f(miniMapWidth, miniMapHeight), sf::Vector2f(WINDOW_WIDTH - (miniMapWidth + 10), WINDOW_HEIGHT - (miniMapHeight + 10)));
    m_miniMap->setDestination(sf::Vector2f(2100, 4800));
    setBG(2);
    srand(time(NULL));


}

sf::Vector2f GamePlay::keyToDirection()
{
    sf::Vector2f direction{ 0, 0 };

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        direction.x -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        direction.x += 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        direction.y -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        direction.y += 1;
    }
    if (direction.x != 0.f || direction.y != 0.f)
    {
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length != 0)
        {
            direction.x /= length;
            direction.y /= length;
        }
    }
    return direction;
}



void GamePlay::draw(sf::RenderWindow& window)
{

    drawBG(window);
    m_board->drawStatic(window);
    m_player->draw(window);
    m_board->drawDynamic(window);
    window.setView(window.getDefaultView());
    m_miniMap->draw(window);
    m_caption->draw(window);

    window.draw(m_pauseButton);

    if (m_paused)
    {
        window.draw(m_buttons[_continueIndex]);
        window.draw(m_buttons[_restartIndex]);
        window.draw(m_buttons[_exitIndex]);
    }
}




void GamePlay::run(sf::RenderWindow& window)
{
    Screen::run(window);
    m_view.setCenter(m_player->getPos());
    m_view.setCenter(clampViewPosition(worldBounds));
    window.setView(m_view);

}



void GamePlay::update(const sf::Time deltaTime)
{
    if (m_paused)return;

    m_clock.decriseTime(deltaTime.asSeconds());
    const auto moveSpeed = 15.f;
    sf::Vector2f direction = keyToDirection();
    m_player->updateSituation(deltaTime);
    m_player->detach();
    if ((direction.x != 0.f || direction.y != 0.f) && !m_player->getIsAttacked())
    {
        m_player->performWalk(deltaTime, direction);

        m_player->notify();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !m_player->getIsAttacked())
    {
        auto bullet = m_player->shoot(deltaTime);
        if (bullet)
        {
            m_board->addBullet(std::move(bullet));

        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !m_player->getIsAttacked())
    {
        auto bullets = m_player->shootGrenade(deltaTime);
        if (!bullets.empty())
        {
            for (auto&& bullet : bullets)
            {
                m_board->addBullet(std::move(bullet));
            }
        }
    }

    m_board->handleCollidePlayer(*m_player.get());
    m_board->updateEnemy(deltaTime, *m_player.get());
    m_board->handleCollideDynamicActives();


    m_miniMap->update(m_player->getPos());
    m_caption->update(m_clock.getTimeLeft(), m_player->getLife(), m_player->getGrenadesAmount(), m_player->getPrisionerAmount(), m_player->getShildMode());
    if (m_clock.getTimeLeft() <= 0)
    {
        endGame("loseEnd.wav", 0);
    }
}

void GamePlay::endGame(const std::string& songName, int picture)
{
    m_controller->makeMusic(songName);
    m_controller->setPictureScreen(picture);
    m_controller->setTimeEnd(m_clock.getTimeHasPassed());
    m_controller->setCurrentScreen(ScreenState::ENDSCREEN);
}



void GamePlay::init()
{
    m_controller->makeMusic("gamePlaySound.wav");

    m_miniMap->deleteAllHouses();

    m_clock.setingTime(180);
    m_player = std::make_unique<Player>(m_clock, AnimationPic, sf::Vector2f(200, 200));
    m_player->endGameFunction([this](const std::string& songName, int picture)
        {
            endGame(songName, picture);
        });

    m_player->setMakeSoundFunction([this](int soundIndex)
        {
            m_controller->makeSound(soundIndex);
        });
    m_caption = std::make_unique<Caption>(worldBounds, sf::Vector2f(100.f, 50.f));
    m_board = std::make_unique<Board>();
    m_board->newGame(*m_miniMap.get(), *m_player.get());

    initButtons();
}

void GamePlay::handleHover(const sf::Vector2f& hoverPos)
{
    if (!m_paused)
    {
        checkPause(hoverPos);
    }
    else
    {
        checkButton(hoverPos, _continue, _continueHL, _continueIndex);
        checkButton(hoverPos, _restart, _restartHL, _restartIndex);
        checkButton(hoverPos, _exitButton, _exitButtonHL, _exitIndex);
    }
}
void GamePlay::initButtons()
{
    m_pauseButton.setTexture(*Resources::instance().getGameButtonText(_pause));
    m_pauseButton.setPosition(1300, 80);

    for (int i = 1; i < (NUM_OF_GBUTTONS / 2); i++)
    {
        sf::Sprite temp;
        temp.setTexture(*Resources::instance().getGameButtonText(i));
        auto pos = sf::Vector2f(620, 450 + (i * buttonOffset * 0.55f));
        temp.setPosition(pos);
        m_buttons.push_back(temp);
    }
}



sf::Vector2f GamePlay::clampViewPosition(const sf::FloatRect& worldBounds)
{

    sf::Vector2f halfSize = m_view.getSize() / 2.0f;


    float minX = worldBounds.left + halfSize.x;
    float maxX = worldBounds.left + worldBounds.width - halfSize.x;
    float minY = worldBounds.top + halfSize.y;
    float maxY = worldBounds.top + worldBounds.height - halfSize.y;

    sf::Vector2f center = m_view.getCenter();

    center.x = std::max(minX, std::min(center.x, maxX));
    center.y = std::max(minY, std::min(center.y, maxY));

    return center;
}

void GamePlay::checkButton(sf::Vector2f hoverPos, GameButtons reg, GameButtons hl, ButtonIndexes index)
{
    if (m_buttons[index].getGlobalBounds().contains(hoverPos))
    {
        m_buttons[index].setTexture(*Resources::instance().getGameButtonText(hl));

        if (reg != m_lastButtonHovered)
        {
            m_lastButtonHovered = int(reg);
            m_controller->makeSound(int(SoundManager::Sounds::HOVER));
        }
    }
    else
        m_buttons[index].setTexture(*Resources::instance().getGameButtonText(reg));
}

void GamePlay::handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window)
{
    if (m_paused)
    {
        if (m_buttons[_continueIndex].getGlobalBounds().contains(clickPos))
            cont();
        else if (m_buttons[_restartIndex].getGlobalBounds().contains(clickPos))
            restart();
        else if (m_buttons[_exitIndex].getGlobalBounds().contains(clickPos))
            exitGame();
    }


    if (m_pauseButton.getGlobalBounds().contains(clickPos))
    {

        m_paused = true;
    }
}

void GamePlay::cont()
{
    m_paused = false;
}

void GamePlay::restart()
{
    init();
    m_paused = false;
}


void GamePlay::exitGame()
{
    m_paused = false;
    m_controller->makeMusic("menuMusic.wav");
    m_controller->setCurrentScreen(ScreenState::MENU);
}

void GamePlay::checkPause(sf::Vector2f hoverPos)
{
    if (m_pauseButton.getGlobalBounds().contains(hoverPos))
    {
        if (!m_hoveredPause)
        {
            m_controller->makeSound(int(SoundManager::Sounds::HOVER));
            m_hoveredPause = true;
        }
        m_pauseButton.setTexture(*Resources::instance().getGameButtonText(_pauseHL));
    }
    else
    {
        m_pauseButton.setTexture(*Resources::instance().getGameButtonText(_pause));
        m_hoveredPause = false;
    }
}
