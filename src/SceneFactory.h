/*
 MIT License
 Copyright (c) 2017 Ruben Moreno Montoliu <ruben3d@gmail.com>
*/
//
// SceneFactory.h - Created on 2017.04.06
//

#ifndef _SCENEFACTORY_H_
#define _SCENEFACTORY_H_

class Scene;
class TextureManager;
class TileFactory;
class LevelLoader;

class SceneFactory
{
public:
	SceneFactory();
	~SceneFactory();

	Scene *create(const std::string& map);

private:
	TextureManager *m_textureManager;
	TileFactory *m_tileFactory;
	LevelLoader *m_levelLoader;
};

#endif /* _SCENEFACTORY_H_ */
