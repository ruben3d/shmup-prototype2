/*
 MIT License
 Copyright (c) 2016 Ruben Moreno Montoliu <ruben3d@gmail.com>
 */
//
// Camera.h - Created on 2016.06.08
//

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <SFML/Graphics.hpp>

class Camera
{
public:
	Camera(const sf::Vector2f& position)
		: m_position(position) {};

	const sf::Vector2f& getPosition() const {return m_position;}
	void setPosition(const sf::Vector2f& position) {m_position = position;}

private:
	sf::Vector2f m_position;
};

#endif /* _CAMERA_H_ */
