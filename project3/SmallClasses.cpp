
#include <ctime>
#include "SmallClasses.h"
#include "TextureManager.h"
using namespace std;
mt19937 SetRandom::rand((unsigned)time(0));


//sets a random integer
int SetRandom::RandInt(int min, int max) {
	uniform_int_distribution<int> dist(min, max);
	return dist(rand);
}

//sets the sprite to a specific number 
SetNum::SetNum(int num) {
	SetSprite("digits");
	GetSprite().setTextureRect(sf::IntRect((num * 21), 0, 21, 32));
}

//sets up a button
Buttons::Buttons(const char* buttonName) {
	SetSprite(buttonName);
}

void Buttons::SetSprite(const char* Sname) {
	this->sprite.setTexture(TextureManager::GetText(Sname));
}

//sets buttons position (under the board)
void Buttons::SetPosition(float x, float y) {
	this->GetSprite().setPosition(x, y);
}

sf::Sprite& Buttons::GetSprite() {
	return this->sprite;
}

//sets a flag sprite
Flags::Flags() {
	SetSprite("flag");
}

//sets a mine sprite 
Mines::Mines() {
	SetSprite("mine");
}

//for neightboring mines, sets the number sprite 
Numbers::Numbers(int num) {
	if (num == 1)
		SetSprite("number_1");
	if (num == 2)
		SetSprite("number_2");
	if (num == 3)
		SetSprite("number_3");
	if (num == 4)
		SetSprite("number_4");
	if (num == 5)
		SetSprite("number_5");
	if (num == 6)
		SetSprite("number_6");
	if (num == 7)
		SetSprite("number_7");
	if (num == 8)
		SetSprite("number_8");
}