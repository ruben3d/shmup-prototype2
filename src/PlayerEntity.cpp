/*
 MIT License
 Copyright (c) 2016 Ruben Moreno Montoliu <ruben3d@gmail.com>
 */
//
// PlayerEnity.cpp
//

#include "PlayerEntity.h"

#include "TextureManager.h"
#include "Camera.h"
#include "Tile.h"
#include "Renderer.h"
#include "Level.h"
#include "MaterialPrototype.h"

PlayerEntity::PlayerEntity(TextureManager *textureManager, Camera *camera, const int levelLength)
	: Entity(new MaterialPrototype("player",
			textureManager->getTexture("ships/player-color.png"),
			textureManager->getTexture("ships/player-specular.png"),
			textureManager->getTexture("ships/player-normal.png"),
			textureManager->getTexture("ships/player-emissive.png"),
			textureManager->getTexture("ships/player-height.png")
		),
		sf::Vector3f(Level::WIDTH*Tile::SIZE/2, levelLength*Tile::SIZE-Renderer::CANVAS_HEIGHT/2, Entity::HEIGHT)
	),
	m_progress(levelLength*Tile::SIZE-Renderer::CANVAS_HEIGHT/2),
	m_camera(camera),
	m_offset(0.0f, 0.0f)
{
	// Nothing
}

PlayerEntity::~PlayerEntity()
{
	delete m_prototype;
}

void PlayerEntity::update(float delta)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) moveLeft(delta);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) moveRight(delta);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) moveUp(delta);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  moveDown(delta);

	m_progress -= GAME_SPEED * delta;
	m_position.x = Level::WIDTH*Tile::SIZE/2 + m_offset.x;
	m_position.y = m_progress + m_offset.y;
	m_camera->setPosition(sf::Vector2f(Renderer::CANVAS_WIDTH/2, m_progress));
	m_sprite.setPosition(sf::Vector2f(m_position.x, m_position.y));
}

void PlayerEntity::moveUp(float delta)
{
	m_offset.y -= delta * INPUT_SPEED;
	m_offset.y = std::max(m_offset.y, Renderer::CANVAS_HEIGHT * -0.5f);
}

void PlayerEntity::moveDown(float delta)
{
	m_offset.y += delta * INPUT_SPEED;
	m_offset.y = std::min(m_offset.y, Renderer::CANVAS_HEIGHT * 0.5f);
}

void PlayerEntity::moveLeft(float delta)
{
	m_offset.x -= delta * INPUT_SPEED;
	m_offset.x = std::max(m_offset.x, Renderer::CANVAS_WIDTH * -0.5f);
}

void PlayerEntity::moveRight(float delta)
{
	m_offset.x += delta * INPUT_SPEED;
	m_offset.x = std::min(m_offset.x, Renderer::CANVAS_WIDTH * 0.5f);
}
