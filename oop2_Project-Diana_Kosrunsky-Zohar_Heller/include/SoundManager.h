#pragma once
#include "Marcos.h"
#include <SFML/Audio.hpp>

class SoundManager
{
public:
	enum class Sounds
	{
		HOVER,
		BONUS,
		CANNON_SHOOT,
		GAME_OVER,
		GRENDE,
		WARPLANES,
		ENGINE,
		SHOOT,
		PRISIONER
	};


	enum class VolumeMode
	{
		INC,
		DEC,
		MUTE
	};


	SoundManager(); 
	~SoundManager() = default; 

	void playSound(const int place);
	void playMusic(const std::string fileName);
	void stopMusic();

	void incVolume();
	void decVolume();
	void muteVolume();

private:
	void setSound(const SoundManager::Sounds soundEnum);
	void setVolume();

	std::vector<sf::Sound> m_sounds;
	sf::Music m_music;
	unsigned int m_volume; 
	unsigned int m_prevVolume; 
};
