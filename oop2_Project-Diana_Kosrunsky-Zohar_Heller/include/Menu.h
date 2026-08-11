#pragma once
#include "Screen.h"
#include "Controller.h"

class Menu : public Screen
{
public:

	Menu(Controller* controller);
	~Menu() = default;


	virtual void update(const sf::Time deltaTime) override;
	virtual void init() override;
	virtual void draw(sf::RenderWindow& window) override;

protected:
	virtual void handleHover(const sf::Vector2f& hoverPos) override;
	virtual void handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window) override;

private:
	virtual void initButtons() override;
	int m_lastButtonHovered = -1;
	std::vector<sf::Text> m_buttons;
};
