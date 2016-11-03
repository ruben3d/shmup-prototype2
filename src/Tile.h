/*
 MIT License
 Copyright (c) 2016 Ruben Moreno Montoliu <ruben3d@gmail.com>
 */
//
// Tile.h - Created on 2016.06.02
//

#ifndef _TILE_H_
#define _TILE_H_

#include <SFML/Graphics.hpp>

#include "Renderer.h"

class MaterialPrototype;

class Tile
{
public:
	static const unsigned int SIZE;

	Tile(const MaterialPrototype *prototype, const float col, const float row);

	const MaterialPrototype *getPrototype() const { return m_prototype; }

private:
	friend class Renderer;
	const sf::Sprite& getSprite() const {return m_sprite;}

	sf::Sprite m_sprite;
	const MaterialPrototype *m_prototype;
};

#endif /* _TILE_H_ */
