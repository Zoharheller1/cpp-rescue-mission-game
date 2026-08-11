#include "VolumeControl.h"

VolumeControl::VolumeControl(Controller* controller)
	: Screen(controller)
{
    initButtons();
	setBG(4);
}

void VolumeControl::update(const sf::Time deltaTime)
{}

void VolumeControl::init()
{}

void VolumeControl::draw(sf::RenderWindow& window)
{
	drawBG(window);
	window.draw(m_returnButton);

	for (auto& button : m_volButtons)
		window.draw(button);
}

void VolumeControl::initButtons()
{
	initRet();
	initVolButtons();
}

void VolumeControl::handleHover(const sf::Vector2f& hoverPos)
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

	for (int i = 0; i < m_volButtons.size(); i++)
		checkButton(hoverPos, i);
}

void VolumeControl::handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window)
{
	if (m_returnButton.getGlobalBounds().contains(clickPos))
		m_controller->setCurrentScreen(ScreenState::MENU);
	else
		for (int i = 0; i < m_volButtons.size(); i++)
			if (m_volButtons[i].getGlobalBounds().contains(clickPos))
				m_controller->manageSound(SoundManager::VolumeMode(i));
}

void VolumeControl::initVolButtons()
{
	for (int i = 0; i < (NUM_OF_VOL_BUTTONS / 2); i++)
	{
		sf::Sprite temp;
		temp.setPosition(volButtonStart.x + buttonOffset * i, volButtonStart.y);
		temp.setTexture(*Resources::instance().getVolText(i));
		m_volButtons.push_back(temp);
	}
}

void VolumeControl::checkButton(sf::Vector2f hoverPos, int index)
{
	if (m_volButtons[index].getGlobalBounds().contains(hoverPos))
		m_volButtons[index].setTexture(*Resources::instance().getVolText(index + (NUM_OF_VOL_BUTTONS / 2)));
	else
		m_volButtons[index].setTexture(*Resources::instance().getVolText(index));
}

void VolumeControl::initRet()
{
	m_returnButton.setString("Return");
	m_returnButton.setFont(*Resources::instance().getFont());
	m_returnButton.setStyle(sf::Text::Style::Bold);
	m_returnButton.setCharacterSize(60);
	auto pos = sf::Vector2f(returnButtonPos.x + buttonOffset / 7, returnButtonPos.y);
	m_returnButton.setPosition(pos);
}
