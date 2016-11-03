/*
 MIT License
 Copyright (c) 2016 Ruben Moreno Montoliu <ruben3d@gmail.com>
 */
//
// Scene.h - Created on 2016.06.4
//

#ifndef _SCENE_H_
#define _SCENE_H_

#include <list>
#include <SFML/Graphics.hpp>
#include "Renderer.h"
#include "math.h"

class Level;
class Entity;
class Camera;
class Light;

class Scene
{
public:
	Scene(Camera *camera, Level *level);
	~Scene();

	void update(float delta);

	const Level *getLevel() const {return m_level;}
	Camera *getCamera() {return m_camera;}
	const Camera *getCamera() const {return m_camera;}

	void addLight(Light *light);
	void removeLight(Light *light);

	void addEntity(Entity *entity);
	void removeEntity(Entity *entity);

	void setAmbientLight(const sf::Color& ambientLight) {m_ambientLight = ambientLight;}
	const sf::Color& getAmbientLight() const {return m_ambientLight;}

	void setSunIntensity(const float intensity) {m_sunIntensity = intensity;}
	float getSunIntensity() const {return m_sunIntensity;}

	void setSunLight(const sf::Color& sunLight) {m_sunLight = sunLight;}
	const sf::Color& getSunLight() const {return m_sunLight;}

	void setSunDir(const sf::Vector3f& sunDir) {m_sunDir = normalize(sunDir);}
	const sf::Vector3f& getSunDir() const {return m_sunDir;}

private:
	friend class Renderer;
	const std::list<Light*>& getLights() const;
	const std::list<Entity*>& getEntities() const;

	Level *m_level;
	std::list<Entity*> m_entities;
	Camera *m_camera;

	std::list<Light*> m_lights;

	float m_sunIntensity;
	sf::Color m_sunLight;
	sf::Color m_ambientLight;
	sf::Vector3f m_sunDir;
};

#endif /* _SCENE_H_ */
