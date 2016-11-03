/*
 MIT License
 Copyright (c) 2016 Ruben Moreno Montoliu <ruben3d@gmail.com>
 */
//
// Scene.cpp - Created on 2016.06.08
//

#include "Scene.h"

#include "Camera.h"
#include "Level.h"
#include "Entity.h"
#include "Light.h"

Scene::Scene(Camera *camera, Level *level)
	: m_camera(camera), m_level(level), m_sunIntensity(1.0f), m_sunLight(200,200,200), m_ambientLight(127,127,127), m_sunDir(0,0,1)
{
	// Nothing
}

Scene::~Scene()
{
	if (m_camera) delete m_camera;
	if (m_level) delete m_level;
	for (auto light : m_lights)
	{
		delete light;
	}
	for (auto entity : m_entities)
	{
		delete entity;
	}
}

void Scene::update(float delta)
{
	for (auto entity : m_entities)
	{
		entity->update(delta);
	}

}

void Scene::addLight(Light *light)
{
	m_lights.push_back(light);
}

void Scene::removeLight(Light *light)
{
	m_lights.remove(light);
}


void Scene::addEntity(Entity *entity)
{
	m_entities.push_back(entity);
}

void Scene::removeEntity(Entity *entity)
{
	m_entities.remove(entity);
}

const std::list<Light*>& Scene::getLights() const
{
	return m_lights;
}

const std::list<Entity*>& Scene::getEntities() const
{
	return m_entities;
}
