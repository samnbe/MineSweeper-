#pragma once
#include <random>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Tile.h"


class SetRandom {
	static std::mt19937 rand;
public:
	static int RandInt(int min, int max);
};


class SetNum : public Tile {
public:
	SetNum(int);
};


class Buttons {
public:
	Buttons(const char* buttonName);
	sf::Sprite sprite;
	void SetSprite(const char* Sname);
	void SetPosition(float x, float y);
	sf::Sprite& GetSprite();
};


class Flags : public Tile {
public:
	Flags();
};


class Mines : public Tile {
public:
	Mines();
};


class Numbers : public Tile {
public:
	Numbers(int);
};


