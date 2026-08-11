#include "EndScreen.h"



EndScreen::EndScreen(Controller* controller)
	: Screen(controller)
{
	initButtons();
	init();
}

void EndScreen::update(const sf::Time deltaTime)
{}


void EndScreen::init()
{
	setBG(m_controller->getPictureScreen());
	int totalTime = static_cast<int>(m_controller->getTimeEnd());
	int minutesStopper = totalTime / 60;
	int secondStopper = totalTime % 60;

	std::ostringstream timeStream;
	timeStream << std::setfill('0') << std::setw(2) << minutesStopper << ":" << std::setfill('0') << std::setw(2) << secondStopper;
	m_time.setString(timeStream.str());
	m_time.setFillColor(sf::Color::Black);
	m_time.setFont(*Resources::instance().getFont());
	m_time.setStyle(sf::Text::Style::Bold);
	m_time.setCharacterSize(90);
	auto poss = sf::Vector2f(280, 560);
	m_time.setPosition(poss);

}


void EndScreen::draw(sf::RenderWindow& window)
{
	drawBG(window);
	window.draw(m_returnButton);
	window.draw(m_time);
}


void EndScreen::initButtons() {initRet();}


void EndScreen::handleHover(const sf::Vector2f& hoverPos)
{
	if (m_returnButton.getGlobalBounds().contains(hoverPos))
	{
		m_returnButton.setOutlineColor(sf::Color::Black);
		m_returnButton.setOutlineThickness(4);
		if (!m_returnHovered)
			m_controller->makeSound(int(SoundManager::Sounds::HOVER));
		m_returnHovered = true;
	}
	else
	{
		m_returnButton.setOutlineThickness(0);
		m_returnHovered = false;
	}
}


void EndScreen::handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window)
{
	if (m_returnButton.getGlobalBounds().contains(clickPos))
	{
		m_controller->makeMusic("menuMusic.wav");
		m_controller->setCurrentScreen(ScreenState::MENU);
	}
}


void EndScreen::initRet()
{
	m_returnButton.setString("Return");
	m_returnButton.setFont(*Resources::instance().getFont());
	m_returnButton.setStyle(sf::Text::Style::Bold);
	m_returnButton.setCharacterSize(60);
	auto pos = sf::Vector2f(returnButtonPos.x + buttonOffset / 6, returnButtonPos.y);
	m_returnButton.setPosition(pos);
}