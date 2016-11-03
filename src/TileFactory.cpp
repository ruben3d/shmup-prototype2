/*
MIT License
Copyright (c) 2016 Ruben Moreno Montoliu <ruben3d@gmail.com>
*/
//
// TileFactory.cpp - Created on 2016.06.01
//

#include <fstream>
#include <json.hpp>
#include "TileFactory.h"
#include "Tile.h"
#include "MaterialPrototype.h"
#include "TextureManager.h"
#include "paths.h"
#include "Logger.h"

using json = nlohmann::json;

TileFactory::TileFactory(const std::string& definitionFilePath, TextureManager *textureManager)
	: m_textureManager(textureManager)
{
	std::ifstream file( buildFullPath(definitionFilePath) );
	json j;
	file >> j;

	for (json::iterator it = j.begin(); it != j.end(); ++it)
	{
		if (it->count("id") != 1)
		{
			// TODO Error
			LOG("error: json - no id");
			continue;
		}
		if (it->count("color") != 1)
		{
			// TODO Error
			LOG("error: json - no color");
			continue;
		}
		if (it->count("specular") > 1)
		{
			// TODO Error
			LOG("error: json - >1 specular");
			continue;
		}
		if (it->count("normal") > 1)
		{
			// TODO Error
			LOG("error: json - >1 normal");
			continue;
		}
		if (it->count("emission") > 1)
		{
			// TODO Error
			LOG("error: json - >1 emission");
			continue;
		}
		if (it->count("height") > 1)
		{
			// TODO Error
			LOG("error: json - >1 height");
			continue;
		}

		const std::string id = (*it)["id"];

		const std::string colorFile = (*it)["color"];
		sf::Texture *color = m_textureManager->getTexture(colorFile);

		sf::Texture *specular = nullptr;
		if (it->count("specular") == 1)
		{
			const std::string specularFile = (*it)["specular"];
			specular = m_textureManager->getTexture(specularFile);
		}

		sf::Texture *normal = nullptr;
		if (it->count("normal") == 1)
		{
			const std::string normalFile = (*it)["normal"];
			normal = m_textureManager->getTexture(normalFile);
		}

		sf::Texture *emission = nullptr;
		if (it->count("emission") == 1)
		{
			const std::string emissionFile = (*it)["emission"];
			emission = m_textureManager->getTexture(emissionFile);
		}

		sf::Texture *height = nullptr;
		if (it->count("height") == 1)
		{
			const std::string heightFile = (*it)["height"];
			height = m_textureManager->getTexture(heightFile);
		}

		MaterialPrototype *prototype = new MaterialPrototype(id, color, specular, normal, emission, height);
		m_prototypes[ id ] = prototype;
	}
}

TileFactory::~TileFactory()
{
	for (auto& pair : m_prototypes) {
    	delete pair.second;
	}
	m_prototypes.clear();
}

Tile *TileFactory::create(const std::string& id, const float col, const float row) const
{
	//LOG(std::string("Creating tile: ")+id);

	Repository::const_iterator it = m_prototypes.find( id );
	if (it == m_prototypes.end())
	{
		LOG("Error: not found");
		return nullptr;
	}

	Tile *tile = new Tile(it->second, col, row);
	return tile;
}
