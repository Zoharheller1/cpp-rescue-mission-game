#include "SoundManager.h"
#include "Resources.h"


SoundManager::SoundManager()
{
	setSound(SoundManager::Sounds::HOVER);
	setSound(SoundManager::Sounds::BONUS);
	setSound(SoundManager::Sounds::CANNON_SHOOT);
	setSound(SoundManager::Sounds::GAME_OVER);
	setSound(SoundManager::Sounds::GRENDE);
	setSound(SoundManager::Sounds::WARPLANES);
	setSound(SoundManager::Sounds::ENGINE);
	setSound(SoundManager::Sounds::SHOOT);
	setSound(SoundManager::Sounds::PRISIONER);
	m_volume = DEFAULT_VOLUME;
	setVolume();
}

void SoundManager::playSound(const int place)
{
	m_sounds[place].play();
}

void SoundManager::playMusic(const std::string fileName)
{
	m_music.openFromFile(fileName);
	m_music.setLoop(true);
	m_music.setVolume(m_volume);
	m_music.play();
}

void SoundManager::stopMusic()
{
	m_music.stop();
}

void SoundManager::setSound(const SoundManager::Sounds soundEnum)
{
	sf::Sound tempSound;
	tempSound.setBuffer(*Resources::instance().getBuffer(int(soundEnum)));
	tempSound.setLoop(false);
	m_sounds.push_back(tempSound);
}

void SoundManager::setVolume()
{
	for (int i = 0; i < m_sounds.size(); i++)
		m_sounds[i].setVolume(m_volume / 2);

	m_music.setVolume(m_volume);
}

void SoundManager::incVolume()
{
	if (m_volume == 100) return;

	m_volume += 10;
	setVolume();
}

void SoundManager::decVolume()
{
	if (m_volume == 0) return;

	m_volume -= 10;
	setVolume();
}

void SoundManager::muteVolume()
{
	if (m_volume == 0)
	{
		m_volume = m_prevVolume;
	}
	else
	{
		m_prevVolume = m_volume;
		m_volume = 0;
	}

	setVolume();
}