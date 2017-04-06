/*
 MIT License
 Copyright (c) 2016 Ruben Moreno Montoliu <ruben3d@gmail.com>
 */
//
// main.cpp - Created on 2016.05.30
//

#include <iostream>
#include <string>

#include "config.h"

#include "Application.h"
#include "SceneFactory.h"
#include "Scene.h"

using namespace std;

bool isCloseEvent(const sf::Event& event)
{
	return event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape);
}

int main(int argc, char const *argv[])
{
	cout << "Applicaton: " << APPLICATION_NAME << " v" << APPLICATION_VERSION_MAJOR << "." << APPLICATION_VERSION_MINOR << "." << APPLICATION_VERSION_REVISION << endl;

	Application *app = new Application();
	Renderer *renderer = app->getRenderer();

	SceneFactory *sceneFactory = new SceneFactory();

	Scene *scene = sceneFactory->create("maps/level01.map");

	while (app->isOpen())
	{
		const float delta = app->startFrame();

		sf::Event event;
		while (app->pollEvent(event))
		{
			if (isCloseEvent(event))
				app->close();
		}

		scene->update(delta);

		renderer->render(scene);
	}

	delete scene;
	delete sceneFactory;
	delete app;

	return 0;
}
