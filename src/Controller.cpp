#include "Controller.h"
#include <iostream>
#include "Gameplay.h"
#include "Menu.h"
#include "Help.h"
#include "VolumeControl.h"
#include "EndScreen.h"

Controller::Controller() : m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "jackal")
{
	m_window.setFramerateLimit(60);
	initScreens();
}


void Controller::run()
{
	sf::Time deltaTime;
	try
	{
		while (m_currentScreen != ScreenState::EXIT)
		{
			deltaTime = m_clock.restart();
			m_window.clear();
			m_screens[int(m_currentScreen)]->draw(m_window);
			m_window.display();
			m_screens[int(m_currentScreen)]->update(deltaTime);
			m_screens[int(m_currentScreen)]->run(m_window);
			swapScreen();
		}
	}
	catch (std::exception& e) {
		std::cerr << e.what();
		exit(EXIT_FAILURE);
	}
}


void Controller::setCurrentScreen(ScreenState state)
{

	m_currentScreen = state;
	m_changeScreen = true;
}

void Controller::setPictureScreen(int state)
{
	m_PictureScreen = state;
}



void Controller::manageSound(SoundManager::VolumeMode action)
{
	switch (action)
	{
	case SoundManager::VolumeMode::INC:
		this->m_sound.incVolume();
		break;

	case SoundManager::VolumeMode::DEC:
		this->m_sound.decVolume();
		break;

	case SoundManager::VolumeMode::MUTE:
		this->m_sound.muteVolume();
		break;

	default:
		break;
	}
}

void Controller::setTimeEnd(float time)
{
	m_TimeLastWIn = time;
}
float Controller::getTimeEnd()
{
	return m_TimeLastWIn;
}

void Controller::initScreens()
{
	m_screens.push_back(std::make_unique<GamePlay>(this));
	m_screens.push_back(std::make_unique<Menu>(this));
	m_screens.push_back(std::make_unique<Help>(this));
	m_screens.push_back(std::make_unique<VolumeControl>(this));
	m_screens.push_back(std::make_unique<EndScreen>(this));
}

void Controller::swapScreen()
{
	if (m_changeScreen)
	{
		if (m_currentScreen == ScreenState::EXIT) exit(EXIT_SUCCESS);
		m_screens[int(m_currentScreen)]->init();
		m_changeScreen = false;
	}
}
