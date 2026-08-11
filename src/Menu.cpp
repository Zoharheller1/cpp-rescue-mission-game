#include "Menu.h"

Menu::Menu(Controller* controller)
	: Screen(controller)
{

	m_controller->makeMusic("menuMusic.wav");
	initButtons();
	init();
}

void Menu::update(const sf::Time deltaTime)
{}

void Menu::init()
{
	setBG(3);

}

void Menu::draw(sf::RenderWindow& window)
{
	drawBG(window);
	for (auto& button : m_buttons)
		window.draw(button);
}

void Menu::initButtons()
{
	sf::Text tempText;
	tempText.setFont(*Resources::instance().getFont());
	tempText.setStyle(sf::Text::Style::Bold);
	tempText.setCharacterSize(70);

	for (int i = 0; i < NUM_OF_MBUTTONS; i++)
	{
		tempText.setString(MENU_BUTTONS_STRINGS[i]);

		tempText.setPosition(sf::Vector2f(screenButtonsStart.x, screenButtonsStart.y + buttonOffset * i));

		m_buttons.push_back(tempText);
	}
}


void Menu::handleHover(const sf::Vector2f& hoverPos)
{
	for (int index = 0; index < m_buttons.size(); index++)
	{
		if (m_buttons[index].getGlobalBounds().contains(hoverPos))
		{
			m_buttons[index].setOutlineColor(sf::Color::Red);
			m_buttons[index].setOutlineThickness(8);
			if (m_lastButtonHovered != index)
				m_controller->makeSound(int(SoundManager::Sounds::HOVER));
			m_lastButtonHovered = index;
			return;
		}
		else
			m_buttons[index].setOutlineThickness(0);
	}
	m_lastButtonHovered = -1;
}


void Menu::handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window)
{
	for (int index = 0; index < m_buttons.size(); index++)
		if (m_buttons[index].getGlobalBounds().contains(clickPos))
		{
			switch (index)
			{

			case MenuButtons::_newGame:
				//	this->m_controller->makeSound(int(Sound::Sounds::BATTLE));
				m_controller->setCurrentScreen(ScreenState::PLAY);
				return;
				// Clicking on help displays info on how to play.
			case MenuButtons::_help:
				m_controller->setCurrentScreen(ScreenState::HELP);
				return;
			case MenuButtons::_sound:
				m_controller->setCurrentScreen(ScreenState::SOUND);
				return;
				// Exits game.
			case MenuButtons::_escape:
				m_controller->setCurrentScreen(ScreenState::EXIT);
				return;
			}
		}
}
