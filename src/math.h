/*
 MIT License
 Copyright (c) 2016 Ruben Moreno Montoliu <ruben3d@gmail.com>
 */
//
// math.h - Created on 2016.06.11
//

#ifndef _MATH_H_
#define _MATH_H_

#include <SFML/Graphics.hpp>

#ifdef min
	#undef min
#endif

#ifdef max
	#undef max
#endif

template <typename T>
T clamp(const T& n, const T& lower, const T& upper) {
	return std::max(lower, std::min(n, upper));
}

float length(const sf::Vector3f& v);

sf::Vector3f& normalize(sf::Vector3f& v);
sf::Vector3f normalize(const sf::Vector3f& v);

sf::Color operator*(const sf::Color& left, const float right);
sf::Color &operator*=(sf::Color &left, const float right);

#endif /* _MATH_H_ */
