#include "Tile.h"
#include <iostream>

//make hiddent tile 
Tile::Tile() {
	SetSprite("tile_hidden");
	isMine = false;
	isOpen = false;
	isFlag = false;
	fakeReveal = false;
}

void Tile::SetSprite(const char* name) {
	this->spriteT.setTexture(TextureManager::GetText(name));
}

sf::Sprite& Tile::GetSprite() {
	return this->spriteT;
}

void Tile::SetPosition(float x, float y) {
	this->GetSprite().setPosition(x, y);
}

//open tile (if no flag)
void Tile::RevealTile() {
	if (!this->IsFlag()) {
		this->SetSprite("tile_revealed");
		this->isOpen = true;
	}
}

//change tile to revealed (for pause button functionality)
void Tile::PauseReveal() {
	this->SetSprite("tile_revealed");
}

void Tile::SetMine() {
	this->isMine = true;
}

//checks if tile has mine
bool Tile::IsMine() {
	return this->isMine;
}

//checks if tile got revelaed already
bool Tile::IsOpen() {
	return this->isOpen;
}

//check is tile has a flag
bool Tile::IsFlag() {
	return this->isFlag;
}

//checks if neighbor tiles have mines
int Tile::CheckNeighborTiles() {
	int count = 0;
	for (int i = 0; i < 8; i++) {
		if (this->neighbors[i] != nullptr) {
			if (this->neighbors[i]->IsMine())
				count++;
		}
	}
	return count;
}

//check value of neighbor tiles
//open neightbor tiles if no mine/flag
void Tile::OpenNeighborTiles() {
	if (this != nullptr && this->CheckNeighborTiles() == 0 && !this->IsMine() && !this->IsFlag()) {
		for (int i = 0; i < 8; i++) {
			if (this->neighbors[i] != nullptr) {
				if (!this->neighbors[i]->IsOpen() && !this->neighbors[i]->IsMine() && !this->IsFlag()) {
					this->neighbors[i]->RevealTile();
					if (this->neighbors[i]->CheckNeighborTiles() == 0) {
						this->neighbors[i]->OpenNeighborTiles();
					}
				}
			}
		}
	}
}

void Tile::PlaceFlag() {
	this->isFlag = true;
}

void Tile::RemoveFlag() {
	this->isFlag = false;
}

//reset tile to default 
void Tile::ResetTile() {
	this->SetSprite("tile_hidden");
	this->isOpen = false;
	isMine = false;
	isFlag = false;
}

void Tile::ChangeFakeReveal() {
	this->fakeReveal = !fakeReveal;
}

bool Tile::GetFakeReveal() {
	return fakeReveal;
}