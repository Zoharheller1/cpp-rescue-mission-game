#pragma once
#include "Screen.h"
#include "Controller.h"

class VolumeControl : public Screen
{
public:

	VolumeControl(Controller* controller);
	~VolumeControl() = default;

	virtual void update(const sf::Time deltaTime) override;
	virtual void init() override;
	virtual void draw(sf::RenderWindow& window) override;

protected:
	virtual void initButtons() override;
	virtual void handleHover(const sf::Vector2f& hoverPos) override;
	virtual void handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window) override;

	
	void initVolButtons();
	void checkButton(sf::Vector2f hoverPos, int index);

private:
	void initRet();
	sf::Text m_returnButton;
	std::vector<sf::Sprite> m_volButtons;
	bool m_returnHovered = false;
};
