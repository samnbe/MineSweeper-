#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
using namespace std;


class TextureManager {
	static unordered_map<string, sf::Texture> textureMap;
	static void LoadText(const char* file);
public:
	static sf::Texture& GetText(const char* name);
	static void Clear();
};
