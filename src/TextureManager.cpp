/*
 MIT License
 Copyright (c) 2016 Ruben Moreno Montoliu <ruben3d@gmail.com>
 */
//
// TextureManager.cpp - Created on 2016.06.01
//

#include "TextureManager.h"
#include "paths.h"

TextureManager::TextureManager()
{
	// Empty
}

TextureManager::~TextureManager()
{
	for (TextureMap::const_iterator it = m_textures.begin(); it != m_textures.end(); it++)
	{
    	delete it->second;
	}
	m_textures.clear();
}

sf::Texture *TextureManager::getTexture(const std::string& textureFilePath)
{
	sf::Texture *texture = NULL;

	TextureMap::const_iterator it = m_textures.find( textureFilePath );
	if (it == m_textures.end())
	{
		texture = new sf::Texture();
		if (!texture->loadFromFile( buildFullPath(textureFilePath) ))
		{
			delete texture;
			return NULL;
		}
		texture->setSmooth(false);
		m_textures[ textureFilePath ] = texture;
	}
	else
	{
	    texture = it->second;
	}
	return texture;
}
