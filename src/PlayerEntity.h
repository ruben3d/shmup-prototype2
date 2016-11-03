/*
 MIT License
 Copyright (c) 2016 Ruben Moreno Montoliu <ruben3d@gmail.com>
 */
//
// PlayerEntity.h - Created on 2016.06.20
//

#ifndef _PLAYERENTITY_H_
#define _PLAYERENTITY_H_

#include "Entity.h"

class TextureManager;
class Camera;

class PlayerEntity : public Entity
{
public:
	constexpr static float GAME_SPEED = 16.0f;	// Pixels per second
	constexpr static float INPUT_SPEED = 48.0f;	// Pixels per second

	PlayerEntity(TextureManager *textureManager, Camera *camera, const int levelLength);
	~PlayerEntity();

	void update(float delta);

	void moveUp(float delta);
	void moveDown(float delta);
	void moveLeft(float delta);
	void moveRight(float delta);

private:
	float m_progress;
	Camera *m_camera;
	sf::Vector2f m_offset;
};

#endif /* _PLAYERENTITY_H_ */
