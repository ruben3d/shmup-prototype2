/*
 MIT License
 Copyright (c) 2016 Ruben Moreno Montoliu <ruben3d@gmail.com>
 */
//
// Entity.cpp - Created on 2016.06.17
//

#include "Entity.h"

#include "MaterialPrototype.h"
#include "Tile.h"
#include "paths.h"

Entity::Entity(const MaterialPrototype *prototype, const sf::Vector3f& position)
	: m_prototype(prototype), m_position(position)
{
	m_sprite.setTexture(*prototype->getColor());
	m_sprite.setPosition(sf::Vector2f(m_position.x, m_position.y));
	m_sprite.setOrigin(sf::Vector2f(Tile::SIZE/2, Tile::SIZE/2));
}

Entity::~Entity()
{
	// Nothing
}
