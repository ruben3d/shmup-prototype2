/*
 MIT License
 Copyright (c) 2016 Ruben Moreno Montoliu <ruben3d@gmail.com>
 */
//
// TextureManager.h - Created on 2016.06.01
//

#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_

#include <string>
#include <map>
#include <SFML/Graphics.hpp>

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	// Memory owned by this class
	// Returns NULL on loading error
	sf::Texture *getTexture(const std::string& textureFilePath);

private:
	TextureManager(const TextureManager&);

	typedef std::map<std::string, sf::Texture*> TextureMap;
	TextureMap m_textures;
};

#endif /* TEXTUREMANAGER_H_ */
