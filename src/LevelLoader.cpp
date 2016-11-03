/*
 MIT License
 Copyright (c) 2016 Ruben Moreno Montoliu <ruben3d@gmail.com>
 */
//
// LevelLoader.cpp - Created on 2016.06.04
//

#include "LevelLoader.h"

#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include "paths.h"
#include "Level.h"
#include "TileFactory.h"
#include "Logger.h"

LevelLoader::LevelLoader(TileFactory *tileFactory)
	: m_tileFactory(tileFactory)
{
	// Nothing
}

LevelLoader::~LevelLoader()
{
	// Nothing
}

Level *LevelLoader::load(const std::string& levelFile)
{
	std::list<std::string> lines;
	std::ifstream file( buildFullPath(levelFile) );
	std::string line;
	while (std::getline(file, line))
	{
		lines.push_back(line);
	}

	Level *level = new Level( lines.size() );

	int row = 0;
	for (auto& line : lines)
	{
		//LOG(line);

		std::istringstream iss(line);
		std::vector<std::string> tokens;
		std::copy(std::istream_iterator<std::string>(iss),
			std::istream_iterator<std::string>(),
			std::back_inserter(tokens));

		for (int col=0; col<Level::WIDTH; col++)
		{
			Tile *tile = m_tileFactory->create( tokens[col], col,row );
			//if (tile) LOG("tile") else LOG("!tile");

			level->setTile( col,row, tile);
		}
		row++;
	}
	return level;
}
