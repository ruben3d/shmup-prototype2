/*
 MIT License
 Copyright (c) 2016 Ruben Moreno Montoliu <ruben3d@gmail.com>
 */
//
// Level.h - Created on 2016.06.04
//

#ifndef _LEVEL_H_
#define _LEVEL_H_

class Tile;

class Level
{
public:
	static const unsigned int WIDTH;

	Level(const unsigned int length);
	~Level();

	unsigned int getLength() const { return m_length; }

	void setTile(const unsigned int col, const unsigned int row, Tile *tile);
	const Tile *getTile(const unsigned int col, const unsigned int row) const;

private:
	const unsigned int m_length;
	Tile ***m_map;
};

#endif /* _LEVEL_H_ */
