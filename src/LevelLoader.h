/*
 MIT License
 Copyright (c) 2016 Ruben Moreno Montoliu <ruben3d@gmail.com>
 */
//
// LevelLoader.h - Created on 2016.06.04
//

#ifndef _LEVELLOADER_H_
#define _LEVELLOADER_H_

#include <string>

class Level;
class TileFactory;

class LevelLoader
{
public:
	LevelLoader(TileFactory *tileFactory);
	~LevelLoader();

	Level *load(const std::string& levelFile);

private:
	TileFactory *m_tileFactory;
};

#endif /* _LEVELLOADER_H_ */
