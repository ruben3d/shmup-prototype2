/*
 MIT License
 Copyright (c) 2016 Ruben Moreno Montoliu <ruben3d@gmail.com>
 */
//
// EnemyEntity.h - Created on 2016.06.20
//

#ifndef _ENEMYENTITY_H_
#define _ENEMYENTITY_H_

#include "Entity.h"

class TextureManager;

class EnemyEntity : public Entity
{
public:
	constexpr static float SPEED = 8.0f;

	EnemyEntity(TextureManager *textureManager, const sf::Vector2f& position);
	~EnemyEntity();

	void update(float delta);
};

#endif /* _ENEMYENTITY_H_ */
