#pragma once
#include "Resources.h"

class Controller;
enum class ScreenState {
	PLAY,
	MENU,
	HELP,
	SOUND,
	ENDSCREEN,
	EXIT
};



class Screen
{
public:

	Screen(Controller* controller) : m_controller(controller) {}
	virtual ~Screen() = default;
	
	virtual void run(sf::RenderWindow& window); 
	virtual void init() = 0;
	virtual void update(const sf::Time deltaTime) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

protected:
	virtual void initButtons() {};
	virtual void handleHover(const sf::Vector2f& hoverPos) {};
	virtual void handleMouseClick(const sf::Vector2f& hoverPos, sf::RenderWindow& window) {};
	void setBG(const int index);

	void drawBG(sf::RenderWindow& window) { window.draw(m_bg); }

	sf::Sprite m_bg;

	Controller* m_controller; 
};

