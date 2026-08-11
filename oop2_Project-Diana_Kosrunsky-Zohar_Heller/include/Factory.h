#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <memory>
#include <map>
#include <string>
#include <functional>


// ================   class Factory   ============================
template <typename T>
class Factory {
public:
	typedef  std::function<std::unique_ptr<T>(const char, const sf::Vector2f&)> CreatorFunc;
	typedef std::map<std::string, CreatorFunc> mymap;
	static std::unique_ptr<T>  create(const std::string& name, const char pic, const sf::Vector2f& location);
	static bool registerit(const std::string& name, CreatorFunc creator);
private:
	static mymap& getMap()
	{
		static mymap m_map;
		return m_map;
	}
};

template <typename T>
std::unique_ptr<T> Factory<T>::create(const std::string& name, const char pic, const sf::Vector2f& location) 
{
	auto it = getMap().find(name);
	if (it == getMap().end())
		return nullptr;
	return it->second(pic, location);
}

template <typename T>
bool Factory<T>::registerit(const std::string& name, CreatorFunc creator) {
	getMap().emplace(name, creator);
	return true;
}

