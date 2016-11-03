/*
 MIT License
 Copyright (c) 2016 Ruben Moreno Montoliu <ruben3d@gmail.com>
 */
//
// MaterialPrototype.h - Created on 2016.06.02
//

#ifndef _MATERIALPROTOTYPE_H_
#define _MATERIALPROTOTYPE_H_

#include <string>
#include <SFML/Graphics.hpp>

class MaterialPrototype
{
public:
	MaterialPrototype(const std::string& id, const sf::Texture *color, const sf::Texture *specular = nullptr, const sf::Texture *normal = nullptr, const sf::Texture *emission = nullptr, const sf::Texture *height = nullptr)
		: m_id(id), m_color(color), m_specular(specular), m_normal(normal), m_emission(emission), m_height(height)
	{
		// Nothing
	}

	MaterialPrototype(const MaterialPrototype& other)
		: m_id(other.m_id), m_color(other.m_color), m_specular(other.m_specular), m_normal(other.m_normal), m_emission(other.m_emission), m_height(other.m_height)
	{
		// Nothing
	}

	~MaterialPrototype()
	{
		// Nothing
	}

	const sf::Texture *getColor() const { return m_color; }
	const sf::Texture *getSpecular() const { return m_specular; }
	const sf::Texture *getNormal() const { return m_normal; }
	const sf::Texture *getEmission() const { return m_emission; }
	const sf::Texture *getHeight() const { return m_height; }

private:
	const std::string m_id;
	const sf::Texture *m_color;
	const sf::Texture *m_specular;
	const sf::Texture *m_normal;
	const sf::Texture *m_emission;
	const sf::Texture *m_height;
};

#endif /* _MATERIALPROTOTYPE_H_ */
