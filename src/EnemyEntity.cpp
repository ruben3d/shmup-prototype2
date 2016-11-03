/*
 MIT License
 Copyright (c) 2016 Ruben Moreno Montoliu <ruben3d@gmail.com>
 */
//
// EnemyEntity.cpp - Created on 2016.06.20
//

#include "EnemyEntity.h"

#include "MaterialPrototype.h"
#include "TextureManager.h"

EnemyEntity::EnemyEntity(TextureManager *textureManager, const sf::Vector2f& position)
	: Entity(new MaterialPrototype("enemy",
			textureManager->getTexture("ships/enemy-color.png"),
			textureManager->getTexture("ships/enemy-specular.png"),
			textureManager->getTexture("ships/enemy-normal.png"),
			textureManager->getTexture("ships/enemy-emissive.png"),
			textureManager->getTexture("ships/enemy-height.png")
		),
		sf::Vector3f(position.x, position.y, Entity::HEIGHT)
	)
{
	// Nothing
}

EnemyEntity::~EnemyEntity()
{
	delete m_prototype;
}

void EnemyEntity::update(float delta)
{
	m_position.y += delta * SPEED;
	m_sprite.setPosition(sf::Vector2f(m_position.x, m_position.y));
}
