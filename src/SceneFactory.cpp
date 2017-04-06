/*
 MIT License
 Copyright (c) 2017 Ruben Moreno Montoliu <ruben3d@gmail.com>
*/
//
// SceneFactory.cpp - Created on 2017.04.06
//

#include <fstream>
#include <random>
#include <string>

#include "SceneFactory.h"

#include "TextureManager.h"
#include "TileFactory.h"
#include "LevelLoader.h"
#include "Camera.h"
#include "Scene.h"
#include "PlayerEntity.h"
#include "EnemyEntity.h"
#include "Light.h"
#include "Tile.h"
#include "Level.h"

#include "Logger.h"

SceneFactory::SceneFactory()
{
	m_textureManager = new TextureManager();
	m_tileFactory = new TileFactory("def/tiles.json", m_textureManager);
	m_levelLoader = new LevelLoader(m_tileFactory);
}

SceneFactory::~SceneFactory()
{
	delete m_levelLoader;
	delete m_tileFactory;
	delete m_textureManager;
}

Scene *SceneFactory::create(const std::string& map)
{
	Level *level = m_levelLoader->load(map);
	Camera *camera = new Camera(sf::Vector2f( Level::WIDTH*Tile::SIZE/2, 100 ));
	Scene *scene = new Scene(camera, level);

	//scene->setAmbientLight(sf::Color(140,150,160));
	//scene->setAmbientLight(sf::Color(93,109,117));
	scene->setAmbientLight(sf::Color(20,25,30));
    scene->setSunIntensity(0.7f);
	scene->setSunLight(sf::Color(255,255,210));
	scene->setSunDir(sf::Vector3f(1,-0.6,1.0));

	PlayerEntity *playerEntity = new PlayerEntity(m_textureManager, camera, level->getLength());
	scene->addEntity(playerEntity);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> randomX(0, Renderer::CANVAS_WIDTH), randomY(0, Tile::SIZE*level->getLength()), randomColor(32, 255), randomRadius(32, 256), randomZ(24, 96);
	for (int i=0; i<30; i++)
	{
		EnemyEntity *enemyEntity = new EnemyEntity(m_textureManager, sf::Vector2f(randomX(gen), randomY(gen) - Renderer::CANVAS_HEIGHT*1.5f));
		scene->addEntity(enemyEntity);

		Light *light = new Light(sf::Vector3f(randomX(gen),randomY(gen),randomZ(gen)), sf::Color(randomColor(gen),randomColor(gen),randomColor(gen)), 0.7f, randomRadius(gen));
		scene->addLight(light);
	}

	return scene;
}
