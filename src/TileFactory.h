/*
MIT License
Copyright (c) 2016 Ruben Moreno Montoliu <ruben3d@gmail.com>
*/
//
// TileFactory.h - Created on 2016.06.01
//

#ifndef _TILEFACTORY_H_
#define _TILEFACTORY_H_

#include <string>
#include <map>

class Tile;
class MaterialPrototype;
class TextureManager;

class TileFactory
{
public:
	TileFactory(const std::string& definitionFilePath, TextureManager *textureManager);
	~TileFactory();

	// Memory owned by caller, not the callee
	Tile *create(const std::string& id, const float col, const float row) const;

private:
	TileFactory(const TileFactory&);

	TextureManager *m_textureManager;
	typedef std::map<std::string,MaterialPrototype*> Repository;
	Repository m_prototypes;
};

#endif /* _TILEFACTORY_H_ */
