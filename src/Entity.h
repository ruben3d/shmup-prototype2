/*
 MIT License
 Copyright (c) 2016 Ruben Moreno Montoliu <ruben3d@gmail.com>
 */
//
// Entity.h - Created on 2016.06.04
//

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "Renderer.h"

class MaterialPrototype;

class Entity
{
public:
	constexpr static float HEIGHT = 48.0f;

	Entity(const MaterialPrototype *prototype, const sf::Vector3f& position);
	virtual ~Entity();

	const MaterialPrototype *getPrototype() const { return m_prototype; }

	const sf::Vector3f& getPosition() const { return m_position; }
	void setPosition(const sf::Vector3f& position) {
		m_position = position;
		m_sprite.setPosition(sf::Vector2f(position.x, position.y));
	}

	virtual void update(float delta) = 0;

protected:
	friend class Renderer;
	const sf::Sprite& getSprite() const {return m_sprite;}

	const MaterialPrototype *m_prototype;
	sf::Vector3f m_position;
	sf::Sprite m_sprite;
};

#endif /* _ENTITY_H_ */
