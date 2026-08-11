#include "Resources.h"
#include <iostream>


Resources::Resources():m_animation(NUMOFANIMATION)
{
	loadTextures();
	m_animation[SIMPLESOLIDER] = simpleSoliderData();
	m_animation[GUARD] = guardData();
	m_animation[SUICIDEBOMBER] = suicideBomberData();
	m_animation[PLAYER] = playerData();
	m_animation[FIRSTSHOT] = firstShotData();
	m_animation[PRISIONER] = prisionerData();
	m_animation[SECONDESHOT]= secondeShotData();
	m_animation[HELICOPTER]= helicopterShotData();
	m_animation[PASSER] = passerData();
	m_animation[CANNON] = cannonData();	
	m_animation[TANK] = tankData();	
	m_animation[GRENADE] = grenadeData();
	m_animation[THIRDSHOT]= thirdShotData();
	m_animation[BATTERY] = batteryData();
}

void Resources::dataOfSpecificLocation(AnimationData& object,Action act, std::vector<sf::Vector2i> size, std::vector<sf::Vector2i> currentStart)
{
	auto itSize = size.begin();
	auto itStart = currentStart.begin();

	for (; itSize != size.end() && itStart != currentStart.end(); ++itSize, ++itStart)
	{
		object.m_data[act].emplace_back(*itStart,*itSize);
	}
}
void Resources::dataOfContinuousObject(AnimationData& object,sf::Vector2i size, sf::Vector2i initSpace, sf::Vector2i middleSpace,Action act,const int whanToStop)
{
	auto currentStart = initSpace;

	auto nextStart = [&]()
		{
			currentStart += middleSpace;
			currentStart.x += size.x;
			return currentStart;
		};
	object.m_data[act].emplace_back(currentStart,size);
	for (int obj = 1; obj < whanToStop; obj++)
	{
		object.m_data[act].emplace_back(nextStart(),size);
	}
}
AnimationData Resources::prisionerData()
{
	auto object = AnimationData{};
	dataOfContinuousObject(object,{47,74},{1368,151},{2,0},Action::WALKING,4);
	dataOfContinuousObject(object,{47,74},{1564,151},{2,0},Action::STANDING,2);
	return object;
}
AnimationData Resources::firstShotData()
{
	auto object = AnimationData{};
	object.m_data[Action::WALKING].emplace_back(sf::Vector2i(18, 519), sf::Vector2i(22, 19));
	dataOfContinuousObject(object,{66,45},{62,502},{20,0},Action::WALKING,5);
	//dataOfSpecificLocation(object, Action::SMALLBOMBER, { {33,29},{44,48} }, { {633,361},{676,357} });
	object.m_data[Action::SMALLBOMBER].emplace_back(sf::Vector2i(676, 357), sf::Vector2i(44, 48));
	return object;
}
AnimationData Resources::cannonData()
{
	auto object = AnimationData{};
	object.m_data[Action::STANDING].emplace_back(sf::Vector2i(18,303), sf::Vector2i(135,64));
	dataOfContinuousObject(object, { 162,64 }, { 168,303 }, { 3,0 }, Action::SHOOTIONG,3);
	return object;
}
AnimationData Resources::grenadeData()
{
	auto object = AnimationData{};
	object.m_data[Action::WALKING].emplace_back(sf::Vector2i(922, 229), sf::Vector2i(31, 30));
	dataOfSpecificLocation(object, Action::DEAD, { {33,29},{44,48},{58,57},{68,73},{79,70},{98,81},{112,83},{121,102},{140,101} },
		{ {633,361},{676,357},{736,354},{803,345},{890,346},{983,343},{1101,343},{1234,334},{1375,330} });
	dataOfSpecificLocation(object, Action::BIGBOMBER, { {33,29},{44,48},{58,57},{68,73},{79,70},{98,81},{112,83},{121,102},{140,101} },
		{ {633,361},{676,357},{736,354},{803,345},{890,346},{983,343},{1101,343},{1234,334},{1375,330} });

	return object;
}

AnimationData Resources::playerData()
{
	auto object = AnimationData{};
	dataOfContinuousObject(object,{140,74},{15,343},{3,0},Action::WALKING,4);
	return object;
}
AnimationData Resources::thirdShotData()
{
	auto object = AnimationData{};
	object.m_data[Action::WALKING].emplace_back(sf::Vector2i(1051, 244), sf::Vector2i(30, 12));
	//dataOfSpecificLocation(object, Action::SMALLBOMBER,{{33,29},{44,48} },{{633,361},{676,357}});
	object.m_data[Action::SMALLBOMBER].emplace_back(sf::Vector2i(676, 357), sf::Vector2i(44, 48));

	return object;
}

AnimationData Resources::tankData()
{
	auto object = AnimationData{};
	dataOfContinuousObject(object,{225,166}, { 18,84 }, { 3,0 }, Action::WALKING,6);
	dataOfContinuousObject(object, {268,166 }, { 1409,84 }, { 3,0 }, Action::SHOOTIONG,4);
	return object;
}

AnimationData Resources::passerData()
{
	auto object = AnimationData{};
	dataOfContinuousObject(object, { 56,36 }, { 1697,175 }, { 3,0 }, Action::WALKING,8);
	object.m_data[Action::DEAD].emplace_back(sf::Vector2i(2114, 221), sf::Vector2i(60, 46));
	return object; 
}
AnimationData Resources::suicideBomberData()
{
	auto object = AnimationData{};
	dataOfContinuousObject(object,{82,99},{17,215},{4,0},Action::HANDSUP,2);
	dataOfContinuousObject(object,{82,99},{189,215},{4,0},Action::WALKING,8);
	dataOfSpecificLocation(object, Action::MEDIUMBOMBER, { {33,29},{44,48},{58,57},{68,73},{79,70},{98,81},{112,83},{121,102}},
		{ {633,361},{676,357},{736,354},{803,345},{890,346},{983,343},{1101,343},{1234,334}});

	return object;
}
AnimationData Resources::guardData()
{
	auto object = AnimationData{};
	dataOfContinuousObject(object,{78,63},{17,135},{5,0}, Action::STANDING,5);
	dataOfContinuousObject(object,{105,80},{459,135},{5,0},Action::SHOOTIONG,5);
	dataOfContinuousObject(object,{105,80},{1009,135},{5,0},Action::DEAD,3);
	return object;
}
AnimationData Resources::simpleSoliderData()
{
	auto object = AnimationData{};
	dataOfContinuousObject(object,{144,74},{16,46},{16,0},Action::WALKING,8);
	dataOfContinuousObject(object,{144,74},{1296,46},{16,0},Action::SHOOTIONG,2);
	object.m_data[Action::SHOOTIONG].emplace_back(sf::Vector2i(1296, 46), sf::Vector2i(144, 74));
	object.m_data[Action::STANDING].emplace_back(sf::Vector2i(1456, 46), sf::Vector2i(144, 74));
	//dataOfContinuousObject(object,{144,74},{1616,46},{16,0},Action::DEAD,4);
	object.m_data[Action::DEAD].emplace_back(sf::Vector2i(1940, 45), sf::Vector2i(107, 78));


	return object;
}
AnimationData Resources::batteryData()
{
	auto object = AnimationData{};
	object.m_data[Action::RED].emplace_back(sf::Vector2i(53,21), sf::Vector2i(25,58));
	object.m_data[Action::ORANGE].emplace_back(sf::Vector2i(86, 21), sf::Vector2i(25,58));
	object.m_data[Action::YELLOW].emplace_back(sf::Vector2i(121, 21), sf::Vector2i(25, 58));
	object.m_data[Action::GRREN].emplace_back(sf::Vector2i(155, 21), sf::Vector2i(25, 58));
	object.m_data[Action::BLUE].emplace_back(sf::Vector2i(189, 21), sf::Vector2i(25, 58));
	return object;
}

AnimationData Resources::helicopterShotData()
{
	auto object = AnimationData{};
	dataOfSpecificLocation(object, Action::STANDING,{ {188,310},{188,310},{188,310},{188,310},{188,310},{188,310},{188,310},{188,310},{188,310} },
	                                            	{ {10, 24}, { 212,21 }, { 434,25 }, { 11,364 }, { 221,364 }, { 436,364 }, {15,681 }, { 224,680 }, { 435,683 }});
	return object;
}
AnimationData Resources::secondeShotData()
{
	auto object = AnimationData{};

	dataOfSpecificLocation(object, Action::WALKING, { {14,10},{17,9},{44,15},{71,21},{76,20},{78,26},{75,27},{75,25},{79,29},{62,38} },
		{ {18,618},{34,618},{57,615},{102,612},{182,613},{264,612},{347,609},{428,609},{511,605},{597,600} });
	dataOfSpecificLocation(object, Action::BIGBOMBER, { {96,282},{183,282},{281,282},{307,282},{389,282},{432,282},{431,282},{408,282},{443,282},{483,282} },
		{ {37,625},{175,629},{388,638},{687,656},{1046,662},{1480,663},{30,1028},{525,1021},{1009,1029},{1529,1016} });
	dataOfSpecificLocation(object, Action::SMALLBOMBER, { {33,29},{44,48} }, { {633,361},{676,357} });
	dataOfSpecificLocation(object, Action::MEDIUMBOMBER, { {33,29},{44,48},{58,57},{68,73},{79,70},{98,81},{112,83},{121,102},{140,101} },
		{ {633,361},{676,357},{736,354},{803,345},{890,346},{983,343},{1101,343},{1234,334},{1375,330} });

	return object;
}
const AnimationData& Resources::animationData(Objects object)
{
	return m_animation[object];
}

void Resources::loadTextures()
{
	std::string filenames[23] = { "battery.png","bush.png","destroyedCar.png","DestroyedHelicopter.png","longwall.png","Gate.png","stone.png",
								  "tree.png","skeleton.png","fallingTree.png","heart.png","weaponAnimation.png","shiled.png","skeletons.png",
		                          "house.png","AnimationPic.png","ruined.png","helicopter.png","smallRuined.png","grenade.png","prisioner.png","Clock.png","spot.png"};
	char currentChar = 'A'; 
	try {
		for (int i = 0; i < 23; i++)
		{

			sf::Texture texture;
			if (!texture.loadFromFile(filenames[i]))
			{
				throw std::runtime_error("Cannot load  load object's texture from file\n");
			}
			m_textureMap[currentChar] = texture;
			currentChar++;

		}

		for (int i = 0; i < NUM_OF_GBUTTONS; i++)
			if (!m_gameButtonsTextures[i].loadFromFile(gameButtonsTexts[i]))
				throw std::runtime_error("Cannot load game button's texture from file\n");

		for (int i = 0; i < 6; i++)
			if (!m_bgTextures[i].loadFromFile(bgTextures[i]))
				throw std::runtime_error("Cannot load background's texture from file\n");

		for (int i = 0; i < soundList.size(); i++)
		{
			sf::SoundBuffer temp;
			if (!temp.loadFromFile(soundList[i]))
			{
				throw std::runtime_error("Cannot load sound buffer from file\n");
				m_buffers.push_back(temp);
			}
			else
				m_buffers.push_back(temp);
		}

		for (int i = 0; i < NUM_OF_VOL_BUTTONS; i++)
			if (!m_volTextures[i].loadFromFile(volTextures[i]))
				throw std::runtime_error("Cannot load projectile's texture from file\n");

		if (!m_font.loadFromFile(MAIN_FONT))
		{
			throw std::runtime_error("Cannot set text font\n");
		}
	}
	catch (std::runtime_error& e)
	{
		std::cerr << e.what();
		exit(EXIT_FAILURE);

	}

}

Resources& Resources::instance()
{
	static Resources inst;
	return inst;
}

Resources::~Resources() {}



const sf::Texture* Resources::getTexture(char pic)const
{
	auto it = m_textureMap.find(pic);
	if (it != m_textureMap.end()) {
		return &it->second;
	}
	return nullptr;
}
