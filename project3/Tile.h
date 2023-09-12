#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

class Tile {
	bool isMine;
	bool isOpen;
	bool isFlag;
	bool fakeReveal;
	int nextMines;
public:
	Tile* neighbors[8];
	sf::Sprite spriteT;
	Tile();
	void SetSprite(const char* name);
	sf::Sprite& GetSprite();
	void SetPosition(float x, float y);
	void RevealTile();
	void PauseReveal(); 
	void SetMine();
	bool IsMine();
	bool IsOpen();
	bool IsFlag();
	int CheckNeighborTiles();
	void OpenNeighborTiles();
	void PlaceFlag();
	void RemoveFlag();
	void ResetTile();
	void ChangeFakeReveal();
	bool GetFakeReveal();
};
