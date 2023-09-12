#include "TextureManager.h"
unordered_map<string, sf::Texture> TextureManager::textureMap;


//sets a filepath to load a texture
//adds to textureMap with the loaded texture
void TextureManager::LoadText(const char* file) {
	string filePath = "files/images/";
	filePath += file;
	filePath += ".png";
	textureMap[file].loadFromFile(filePath);
}

//laods a texture if not already in map
//return that sprite 
sf::Texture& TextureManager::GetText(const char* name) {
	if (textureMap.find(name) == textureMap.end()) {
		LoadText(name);
	}
	return textureMap[name];
}

//clears textureMap
void TextureManager::Clear() {
	textureMap.clear();
}