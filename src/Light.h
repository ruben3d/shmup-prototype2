/*
 MIT License
 Copyright (c) 2016 Ruben Moreno Montoliu <ruben3d@gmail.com>
 */
//
// Light.h - Created on 2016.06.08
//

#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <SFML/Graphics.hpp>

class Light
{
public:
	Light(const sf::Vector3f& position, const sf::Color& color, const float intensity, const float radius)
		: m_position(position), m_color(color), m_intensity(intensity), m_radius(radius) {};

	const sf::Vector3f& getPosition() const {return m_position;}
	void setPosition(const sf::Vector3f& position) {m_position = position;}

	const sf::Color& getColor() const {return m_color;}
	void setColor(const sf::Color& color) {m_color = color;}

	float getIntensity() const {return m_intensity;}
	void setIntensity(const float intensity) {m_intensity = intensity;}

	float getRadius() const {return m_radius;}
	void setRadius(const float radius) {m_radius = radius;}

private:
	sf::Vector3f m_position;
	sf::Color m_color;
	float m_intensity;
	float m_radius;
};

#endif /* _LIGHT_H_ */
