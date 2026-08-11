#pragma once
#include "Screen.h"
#include "CustomClock.h"
#include <iostream>

class Controller
{
public:

	Controller();
	~Controller() = default;

	void setPictureScreen(int state);
	void run();
	void setCurrentScreen(ScreenState state);
	void manageSound(SoundManager::VolumeMode action);
	void makeSound(int index) { m_sound.playSound(index); }
	void setTimeEnd(float time);
	void makeMusic(const std::string fileName) { m_sound.playMusic(fileName); }

	int getPictureScreen()const { return m_PictureScreen; }

	float getTimeEnd();

private:

	void initScreens();
	void swapScreen();

	std::vector<std::unique_ptr<Screen>> m_screens;

	ScreenState m_currentScreen = ScreenState::MENU;

	int m_PictureScreen;

	bool m_changeScreen = false;

	float m_TimeLastWIn;

	sf::RenderWindow m_window;
	sf::Clock m_clock;
	SoundManager m_sound;
};




