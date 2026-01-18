#include "ResourceManager.h"
#include <Windows.h>

ResourceManager* ResourceManager::m_instance = nullptr;

sf::Texture* ResourceManager::loadTexture(std::string _path) {

	if (!textureCache.contains(_path)) {
		TCHAR buffer[MAX_PATH];
		GetModuleFileName(NULL, buffer, sizeof(buffer));
		std::string absolutePath = std::filesystem::path(buffer).parent_path().string();

		textureCache.insert({ _path, new sf::Texture(absolutePath + "\\"+ _path)});
	}

	return textureCache[_path];
}

void ResourceManager::unloadTexture(std::string _path) {
	textureCache.erase(_path);
}

sf::Font* ResourceManager::loadFont(std::string _path) {

	if (!fontCache.contains(_path)) {
		TCHAR buffer[MAX_PATH];
		GetModuleFileName(NULL, buffer, sizeof(buffer));
		std::string absolutePath = std::filesystem::path(buffer).parent_path().string();

		fontCache.insert({ _path, new sf::Font(absolutePath + "\\" + _path) });
	}

	return fontCache[_path];
}

void ResourceManager::unloadFont(std::string _path) {
	fontCache.erase(_path);
}

ResourceManager* ResourceManager::instance()
{
	if (m_instance == nullptr) {
		m_instance = new ResourceManager();
	}
	return m_instance;
}