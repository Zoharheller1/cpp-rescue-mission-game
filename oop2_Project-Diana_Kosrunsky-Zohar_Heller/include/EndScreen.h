#pragma once
#include "Screen.h"
#include "Controller.h"
#include <sstream>
#include <iomanip>
#include <iostream>

class EndScreen : public Screen
{
public:
	EndScreen(Controller* controller);
	~EndScreen() = default;

	virtual void update(const sf::Time deltaTime) override;
	virtual void init() override;
	virtual void draw(sf::RenderWindow& window) override;

protected:
	virtual void handleHover(const sf::Vector2f& hoverPos) override;
	virtual void handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window) override;

private:

	void initRet();
	virtual void initButtons() override;
	sf::Text m_returnButton;
	sf::Text m_time;
	bool m_returnHovered = false;
};
