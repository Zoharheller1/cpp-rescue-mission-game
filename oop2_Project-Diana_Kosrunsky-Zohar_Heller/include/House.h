#pragma once
#include <SFML/Graphics.hpp>
#include "ReplacePicture.h"
#include "Factory.h"
#include "Subject.h"
#include "MiniMap.h"

class House :public ReplacePicture, public Subject
{
public:

	House(const char pic, const sf::Vector2f& location);
	~House() = default;

	virtual void notifyObservers() override;
	virtual	void attachObserver(Observer* obs);
	virtual void detachObserver() override;
	virtual void handleCollisionWithBullet() override = 0;
private:
	Observer* observer;
};