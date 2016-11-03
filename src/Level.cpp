/*
 MIT License
 Copyright (c) 2016 Ruben Moreno Montoliu <ruben3d@gmail.com>
 */
//
// Level.cpp - Created on 2016.06.04
//

#include "Level.h"

#include <cstddef>
#include "Tile.h"

const unsigned int Level::WIDTH = 10;

Level::Level(const unsigned int length)
	: m_length(length)
{
	m_map = new Tile**[length];
	for (int j=0; j<m_length; j++)
	{
		m_map[j] = new Tile*[WIDTH];
		for (int i=0; i<WIDTH; i++)
		{
			m_map[j][i] = NULL;
		}
	}
}

Level::~Level()
{
	for (int j=0; j<m_length; j++)
	{
		for (int i=0; i<WIDTH; i++)
		{
			if (m_map[j][i])
			{
				delete m_map[j][i];
			}
		}
		delete[] m_map[j];
	}
	delete[] m_map;
	m_map = NULL;
}

void Level::setTile(const unsigned int col, const unsigned int row, Tile *tile)
{
	m_map[row][col] = tile;
}

const Tile *Level::getTile(const unsigned int col, const unsigned int row) const
{
	return m_map[row][col];
}
