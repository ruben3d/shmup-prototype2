/*
 MIT License
 Copyright (c) 2016 Ruben Moreno Montoliu <ruben3d@gmail.com>
 */
//
// math.cpp - Created on 2016.06.11
//

#include "math.h"

#include <cmath>

float length(const sf::Vector3f& v)
{
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

sf::Vector3f& normalize(sf::Vector3f& v)
{
	return v /= length(v);
}

sf::Vector3f normalize(const sf::Vector3f& v)
{
	sf::Vector3f w(v);
	return w /= length(v);
}

sf::Color operator*(const sf::Color& left, const float right)
{
	return sf::Color(	static_cast<sf::Uint8>( clamp(left.r*right, 0.0f,255.0f) ),
						static_cast<sf::Uint8>( clamp(left.g*right, 0.0f,255.0f) ),
						static_cast<sf::Uint8>( clamp(left.b*right, 0.0f,255.0f) ),
						left.a );
}


sf::Color &operator*=(sf::Color &left, const float right)
{
	left.r = static_cast<sf::Uint8>( clamp(left.r*right, 0.0f,255.0f) );
	left.g = static_cast<sf::Uint8>( clamp(left.g*right, 0.0f,255.0f) );
	left.b = static_cast<sf::Uint8>( clamp(left.b*right, 0.0f,255.0f) );
	return left;
}
