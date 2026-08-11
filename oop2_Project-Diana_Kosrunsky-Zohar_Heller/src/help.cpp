#include "Help.h"

Help::Help(Controller* controller)
	: Screen(controller)
{
	initButtons();
	init();
}

void Help::update(const sf::Time deltaTime){}


void Help::init(){setBG(5);}


void Help::draw(sf::RenderWindow& window)
{
	drawBG(window);
	window.draw(m_returnButton);
}


void Help::initButtons()
{
	initRet();
}


void Help::handleHover(const sf::Vector2f& hoverPos)
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


void Help::handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window)
{
	if (m_returnButton.getGlobalBounds().contains(clickPos))
	{
		m_controller->setCurrentScreen(ScreenState::MENU);
	}

}


void Help::initRet()
{
	m_returnButton.setString("Return");
	m_returnButton.setFont(*Resources::instance().getFont());
	m_returnButton.setStyle(sf::Text::Style::Bold);
	m_returnButton.setCharacterSize(60);
	auto pos = sf::Vector2f(returnButtonPos.x + buttonOffset / 6, returnButtonPos.y);
	m_returnButton.setPosition(pos);
}