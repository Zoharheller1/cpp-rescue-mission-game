#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Marcos.h"
#include <unordered_map>
#include "SoundManager.h"
#include "AnimationData.h"

class Resources
{
public:
	~Resources();

	enum Objects
	{
		SIMPLESOLIDER,
		GUARD,
		SUICIDEBOMBER,
		PLAYER,
		FIRSTSHOT,
		PRISIONER,
		SECONDESHOT,
		HELICOPTER,
		PASSER,
		CANNON,
		TANK,
		GRENADE,
		THIRDSHOT,
		BATTERY,
		NUMOFANIMATION,
	};

	static Resources& instance();
	const sf::Texture* getTexture(char c)const;
	const sf::Texture* getBackground(int i)	const { return &m_bgTextures[i]; }
	const sf::Font* getFont() const { return &m_font; };
	const sf::Texture* getVolText(int i)	const { return &m_volTextures[i]; }
	const sf::SoundBuffer* getBuffer(int i)			const { return &m_buffers[i]; }
	const AnimationData& animationData(Objects object);
	const sf::Texture* getGameButtonText(int i)		const { return &m_gameButtonsTextures[i]; }

private:
	Resources();
	Resources(const Resources&) = default;
	Resources& operator=(const Resources&) = default;
	sf::Texture m_bgTextures[6];
	void loadTextures();
	std::vector<sf::SoundBuffer> m_buffers;
	sf::Font m_font;
	sf::Texture m_volTextures[NUM_OF_VOL_BUTTONS];
	sf::Texture m_gameButtonsTextures[NUM_OF_GBUTTONS];
	std::unordered_map<char, sf::Texture> m_textureMap;
	std::vector<AnimationData> m_animation;
	AnimationData playerData();
	AnimationData simpleSoliderData();
	AnimationData guardData();
	AnimationData suicideBomberData();
	AnimationData firstShotData();
	AnimationData prisionerData();
	AnimationData secondeShotData();
	AnimationData helicopterShotData();
	AnimationData passerData();
	AnimationData cannonData();
	AnimationData tankData();
	AnimationData grenadeData();
	AnimationData batteryData();
	AnimationData thirdShotData();
	void dataOfContinuousObject(AnimationData& object, sf::Vector2i size, sf::Vector2i initSpace, sf::Vector2i middleSpace, Action act, const int);
	void dataOfSpecificLocation(AnimationData& object, Action act, std::vector<sf::Vector2i>, std::vector<sf::Vector2i>);
};
