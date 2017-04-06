/*
 MIT License
 Copyright (c) 2016 Ruben Moreno Montoliu <ruben3d@gmail.com>
 */
//
// main.cpp - Created on 2016.05.30
//

#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include "config.h"
#include "TextureManager.h"
#include "TileFactory.h"
#include "Tile.h"
#include "Application.h"
#include "Camera.h"
#include "Scene.h"
#include "Level.h"
#include "LevelLoader.h"
#include "Logger.h"
#include "Light.h"
#include "PlayerEntity.h"
#include "EnemyEntity.h"

using namespace std;

int main(int argc, char const *argv[])
{
	cout << "Applicaton: " << APPLICATION_NAME << " v" << APPLICATION_VERSION_MAJOR << "." << APPLICATION_VERSION_MINOR << "." << APPLICATION_VERSION_REVISION << endl;
	Logger::Log("Logger");

	TextureManager *textureManager = new TextureManager();
	TileFactory *tileFactory = new TileFactory("def/tiles.json", textureManager);

	Application *app = new Application();
	Renderer *renderer = app->getRenderer();

	LevelLoader levelLoader(tileFactory);
	Level *level = levelLoader.load("maps/level01.map");

	Camera *camera = new Camera(sf::Vector2f( Level::WIDTH*Tile::SIZE/2, 100 ));

	Scene *scene = new Scene(camera, level);
	//scene->setAmbientLight(sf::Color(140,150,160));
	//scene->setAmbientLight(sf::Color(93,109,117));
	scene->setAmbientLight(sf::Color(20,25,30));
    scene->setSunIntensity(0.7f);
	scene->setSunLight(sf::Color(255,255,210));
	scene->setSunDir(sf::Vector3f(1,-0.6,1.0));

	PlayerEntity *playerEntity = new PlayerEntity(textureManager, camera, level->getLength());
	scene->addEntity(playerEntity);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> randomX(0, Renderer::CANVAS_WIDTH), randomY(0, Tile::SIZE*level->getLength()), randomColor(32, 255), randomRadius(32, 256), randomZ(24, 96);
	for (int i=0; i<30; i++)
	{
		EnemyEntity *enemyEntity = new EnemyEntity(textureManager, sf::Vector2f(randomX(gen), randomY(gen) - Renderer::CANVAS_HEIGHT*1.5f));
		scene->addEntity(enemyEntity);

		Light *light = new Light(sf::Vector3f(randomX(gen),randomY(gen),randomZ(gen)), sf::Color(randomColor(gen),randomColor(gen),randomColor(gen)), 0.7f, randomRadius(gen));
		scene->addLight(light);
	}

	while (app->isOpen())
	{
		const float delta = app->startFrame();
		sf::Event event;
		while (app->pollEvent(event))
		{
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) )
				app->close();
		}

		scene->update(delta);

		renderer->render(scene);
	}

	delete scene;
	delete app;
	delete tileFactory;
	delete textureManager;

	return 0;
}
