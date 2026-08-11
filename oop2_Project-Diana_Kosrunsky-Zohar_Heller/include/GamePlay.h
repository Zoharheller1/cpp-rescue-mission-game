#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"
#include "Marcos.h"
#include <cmath>
#include <ctime>
#include <memory>
#include <vector>
#include "CustomClock.h"
#include "Player.h"
#include "Board.h"
#include "Screen.h"
#include "Caption.h"
#include "Controller.h"

class GamePlay : public Screen
{
public:
	GamePlay(Controller* controller);
	virtual ~GamePlay() = default;

	virtual void run(sf::RenderWindow& window)override;
	virtual void init() override;
	virtual void update(const sf::Time deltaTime) override;
	virtual void draw(sf::RenderWindow& window) override;
	void endGame(const std::string& songName, int);
protected:
	virtual void handleHover(const sf::Vector2f& hoverPos) override;
	virtual void handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window) override;

private:
	void cont();
	void checkButton(sf::Vector2f hoverPos, GameButtons reg, GameButtons hl, ButtonIndexes index);
	virtual void initButtons() override;
	void checkPause(sf::Vector2f hoverPos);
	sf::Vector2f clampViewPosition(const sf::FloatRect& worldBounds);
	sf::Vector2f keyToDirection();
	void exitGame();
	void restart();
	sf::Sprite m_pauseButton;
	bool m_paused = false;
	std::unique_ptr < Player> m_player;
	std::unique_ptr< Caption> m_caption;
	sf::FloatRect worldBounds;
	std::unique_ptr < Board> m_board;
	std::vector<sf::Sprite> m_buttons;
	std::unique_ptr<MiniMap> m_miniMap;
	sf::View m_view;
	CustomClock  m_clock;
	int m_lastButtonHovered = -1;
	bool m_hoveredPause = false;
};