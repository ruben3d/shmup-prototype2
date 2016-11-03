/*
 MIT License
 Copyright (c) 2016 Ruben Moreno Montoliu <ruben3d@gmail.com>
 */
//
// Tile.cpp - Created on 2016.06.03
//

#include "Tile.h"
#include "MaterialPrototype.h"
#include "Logger.h"

const unsigned int Tile::SIZE = 32;

Tile::Tile(const MaterialPrototype *prototype, const float col, const float row)
	: m_prototype(prototype)
{
	m_sprite.setTexture(*prototype->getColor());
	m_sprite.setPosition(sf::Vector2f(col * SIZE, row * SIZE));
}
