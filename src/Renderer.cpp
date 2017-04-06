/*
 MIT License
 Copyright (c) 2016 Ruben Moreno Montoliu <ruben3d@gmail.com>
 */
//
// Renderer.cpp - Created on 2016.06.07
//

#include "Renderer.h"

#include <cmath>
#include "Logger.h"
#include "Application.h"
#include "paths.h"
#include "Scene.h"
#include "Camera.h"
#include "Level.h"
#include "Tile.h"
#include "MaterialPrototype.h"
#include "Light.h"
#include "Entity.h"

const int Renderer::CANVAS_WIDTH = 320;
const int Renderer::CANVAS_HEIGHT = 200;

Renderer::Renderer(sf::RenderWindow *renderWindow, const int appWidth, const int appHeight)
	: m_screen(renderWindow), APP_WIDTH(appWidth), APP_HEIGHT(appHeight), m_canvas(nullptr)
{
	// Times the whole canvas fits into the screen (whole number)
	const int canvasSizeMultiplier = computeCanvasSizeMultiplier();

	// The canvas will be rendered at the multiplied size
	m_canvas = createCanvas(canvasSizeMultiplier);

	setCanvasDisplaySettings(canvasSizeMultiplier);

	m_colorGradingShader = createShader("shaders/basic.vs", "shaders/colorgrading.fs");
	m_colorGradingTable = createColorGradingTable();

	m_tileBaseShader = createShader("shaders/basic.vs", "shaders/tile-base.fs");
	m_tileBaseEmissionShader = createShader("shaders/basic.vs", "shaders/tile-base-emission.fs");
	m_tileLightOmniShader = createShader("shaders/tile-omni.vs", "shaders/tile-omni.fs");
}

Renderer::~Renderer()
{
	delete m_tileLightOmniShader;
	delete m_tileBaseEmissionShader;
	delete m_tileBaseShader;
	delete m_colorGradingShader;
	delete m_colorGradingTable;
	delete m_canvas;
}

int Renderer::computeCanvasSizeMultiplier() const
{
	const int timesWidth = floor(APP_WIDTH / CANVAS_WIDTH);
	const int timesHeight = floor(APP_HEIGHT / CANVAS_HEIGHT);
	const int multiplier = timesWidth < timesHeight ? timesWidth : timesHeight;
	return multiplier;
}

sf::RenderTexture *Renderer::createCanvas(const int canvasSizeMultiplier) const
{
	sf::RenderTexture *canvas = new sf::RenderTexture();

	if (!canvas->create(CANVAS_WIDTH * canvasSizeMultiplier, CANVAS_HEIGHT * canvasSizeMultiplier))
	{
		// TODO Exception
		LOG("canvas->create - error");
	}
	canvas->setSmooth(true);

	return canvas;
}

void Renderer::setCanvasDisplaySettings(const int canvasSizeMultiplier)
{
	const float screen_ratio = APP_WIDTH / (float) APP_HEIGHT;
	const float canvas_ratio = CANVAS_WIDTH / (float) CANVAS_HEIGHT;

	// If the screen is wider than the canvas
	if (screen_ratio > canvas_ratio)
	{
		m_canvasTop = 0.0f;
		m_canvasLeft = (1.0f - canvas_ratio/screen_ratio) / 2.0f;

		m_canvasScale = APP_HEIGHT / (float) (CANVAS_HEIGHT * canvasSizeMultiplier);
	}
	else // If the screen is taller than the canvas
	{
		m_canvasTop = (1.0f - screen_ratio/canvas_ratio) / 2.0f;
		m_canvasLeft = 0.0f;

		m_canvasScale = APP_WIDTH / (float) (CANVAS_WIDTH * canvasSizeMultiplier);
	}
}

sf::Shader *Renderer::createShader(const std::string& verterShader, const std::string& fragmentShader)
{
	sf::Shader *shader = new sf::Shader();
	if (!shader->loadFromFile( buildFullPath(verterShader), buildFullPath(fragmentShader) ))
	{
		// TODO Error
		LOG("shader - error");
	}
	return shader;
}

sf::Texture *Renderer::createColorGradingTable()
{
	sf::Texture *table = new sf::Texture();
        if (!table->loadFromFile( buildFullPath("fx/color-neutral.png") ))
	{
		// TODO Error
		LOG("ColorGradingTable - error");
	}
	table->setSmooth(true);
	return table;
}

void Renderer::render(const Scene *scene)
{
	m_canvas->setView(createGameView(scene));

	m_canvas->clear();

	renderLevel(scene);
	renderEntities(scene);

	m_canvas->display();

	renderCanvasToScreen();
}

void Renderer::renderLevel(const Scene *scene)
{
	renderTileBase(scene);

	if (hasLights(scene))
	{
		renderTileLights(scene);
	}
}

void Renderer::renderTileBase(const Scene *scene)
{
	const Level *level = scene->getLevel();

	for (int j=0; j<level->getLength(); j++)
	for (int i=0; i<Level::WIDTH; i++)
	{
		const Tile *tile = level->getTile(i,j);
		renderSpriteBase(scene, tile->getSprite(), tile->getPrototype());
	}
}

void Renderer::renderSpriteBase(const Scene *scene, const sf::Sprite& sprite, const MaterialPrototype *prototype)
{
	const sf::Color& ambientLight = scene->getAmbientLight();
	const sf::Color sunLight = scene->getSunLight() * scene->getSunIntensity();
	const sf::Vector3f& sunDir = scene->getSunDir();

	sf::Shader *shader;
	if (prototype->getEmission())
	{
		shader = m_tileBaseEmissionShader;
		shader->setParameter("sEmission", *prototype->getEmission());
	}
	else
	{
		shader = m_tileBaseShader;
	}
	shader->setParameter("sDiffuse", sf::Shader::CurrentTexture);
	shader->setParameter("sSpecular", *prototype->getSpecular());
	shader->setParameter("sNormal", *prototype->getNormal());
	shader->setParameter("uAmbientLight", ambientLight);
	shader->setParameter("uSunLight", sunLight);
	shader->setParameter("uSunDir", sunDir);

	m_canvas->draw(sprite, shader);
}

bool Renderer::hasLights(const Scene *scene)
{
	return scene->getLights().size() > 0;
}

void Renderer::renderTileLights(const Scene *scene)
{
	for (const auto light : scene->getLights())
	{
		if (isLightOnCamera(scene->getCamera(), light))
		{
			renderLightTiles(scene, light);
		}
	}
}

bool Renderer::isLightOnCamera(const Camera *camera, const Light *light)
{
	const sf::Vector2f& camPos = camera->getPosition();
	const float camTopBound = camPos.y - CANVAS_HEIGHT/2;
	const float camBottomBound = camPos.y + CANVAS_HEIGHT/2;
	const sf::Vector3f& lightPos = light->getPosition();
	const float lightRadius = light->getRadius();

	if ( (lightPos.y + lightRadius) < camTopBound ) return false;
	if ( (lightPos.y - lightRadius) > camBottomBound ) return false;

	return true;
}

void Renderer::renderLightTiles(const Scene *scene, const Light *light)
{
	const Level *level = scene->getLevel();

	const sf::Vector3f& lightPos = light->getPosition();
	const float lightRadius = light->getRadius();

	const int lightTop = static_cast<int>((lightPos.y - lightRadius) / Tile::SIZE);
	const int lightBottom = static_cast<int>((lightPos.y + lightRadius) / Tile::SIZE);
	const int lightLeft = static_cast<int>((lightPos.x - lightRadius) / Tile::SIZE);
	const int lightRight = static_cast<int>((lightPos.x + lightRadius) / Tile::SIZE);

	const sf::Vector2f& camPos = scene->getCamera()->getPosition();

	const int camTop = static_cast<int>((camPos.y - CANVAS_HEIGHT/2) / Tile::SIZE );
	const int camBottom = static_cast<int>((camPos.y + CANVAS_HEIGHT/2) / Tile::SIZE);

	const int top = std::max( std::max(camTop, lightTop), 0);
	const int bottom = std::min( std::min(camBottom, lightBottom), static_cast<int>(level->getLength())-1 );
	const int left = std::max(0, lightLeft);
	const int right = std::min(static_cast<int>(Level::WIDTH)-1, lightRight);

	for (int j=top; j<=bottom; j++)
	for (int i=left; i<=right; i++)
	{
		const Tile *tile = level->getTile(i,j);
		renderSpriteLight(tile->getSprite(), tile->getPrototype(), light);
	}
}

void Renderer::renderSpriteLight(const sf::Sprite& sprite, const MaterialPrototype *prototype, const Light *light)
{
	const sf::Color lightColor = light->getColor() * light->getIntensity();
	const sf::Vector3f& lightPos = light->getPosition();
	const float lightRadius = light->getRadius();

	m_tileLightOmniShader->setParameter("sDiffuse", sf::Shader::CurrentTexture);
	m_tileLightOmniShader->setParameter("sSpecular", *prototype->getSpecular());
	m_tileLightOmniShader->setParameter("sNormal", *prototype->getNormal());
	m_tileLightOmniShader->setParameter("sHeight", *prototype->getHeight());
	m_tileLightOmniShader->setParameter("uLightPos", lightPos);
	m_tileLightOmniShader->setParameter("uLightColor", lightColor);
	m_tileLightOmniShader->setParameter("uLightRadius", lightRadius);
	m_tileLightOmniShader->setParameter("uTileHeight", 0.0f);

	sf::RenderStates renderStates;
	renderStates.blendMode = sf::BlendAdd;
	renderStates.shader = m_tileLightOmniShader;
	m_canvas->draw(sprite, renderStates);
}

void Renderer::renderEntities(const Scene *scene)
{
	for (const auto entity : scene->getEntities())
	{
		renderEntity(scene, entity);
	}
}

void Renderer::renderEntity(const Scene *scene, const Entity *entity)
{
	renderSpriteBase(scene, entity->getSprite(), entity->getPrototype());
	renderEntityLights(scene, entity);
}

void Renderer::renderEntityLights(const Scene *scene, const Entity *entity)
{
	for (const auto light : scene->getLights())
	{
		if (isLightOnCamera(scene->getCamera(), light))
		{
			renderEntityLight(scene, entity, light);
		}
	}
}

void Renderer::renderEntityLight(const Scene *scene, const Entity *entity, const Light *light)
{
	const Level *level = scene->getLevel();

	const sf::Vector3f& lightPos = light->getPosition();
	const float lightRadius = light->getRadius();

	const float lightTop = lightPos.y - lightRadius;
	const float lightBottom = lightPos.y + lightRadius;
	const float lightLeft = lightPos.x - lightRadius;
	const float lightRight = lightPos.x + lightRadius;

	const sf::Vector2f& camPos = scene->getCamera()->getPosition();

	const float camTop = camPos.y - CANVAS_HEIGHT/2;
	const float camBottom = camPos.y + CANVAS_HEIGHT/2;

	const float top = std::max( std::max(camTop, lightTop), 0.0f);
	const float bottom = std::min( std::min(camBottom, lightBottom), static_cast<float>(level->getLength()-1)*Tile::SIZE );
	const float left = std::max(0.0f, lightLeft);
	const float right = std::min(Level::WIDTH*Tile::SIZE-1.0f, lightRight);

	if (isEntityLighted(top, bottom, left, right, entity))
	{
		renderSpriteLight(entity->getSprite(), entity->getPrototype(), light);
	}
}

bool Renderer::isEntityLighted(const float top, const float bottom, const float left, const float right, const Entity* entity)
{
	const sf::Vector3f& pos = entity->getPosition();
	return ((pos.y+Tile::SIZE >= top)
		&& (pos.y-Tile::SIZE <= bottom)
		&& (pos.x+Tile::SIZE >= left)
		&& (pos.x-Tile::SIZE <= right));
}

const sf::View Renderer::createGameView(const Scene *scene) const
{
	const sf::Vector2f& position = scene->getCamera()->getPosition();
	return sf::View(position, sf::Vector2f(CANVAS_WIDTH, CANVAS_HEIGHT));
}

void Renderer::renderCanvasToScreen()
{
	const sf::Texture& canvasTexture = m_canvas->getTexture();

	sf::Sprite canvasSprite(canvasTexture);
	canvasSprite.setScale(m_canvasScale, m_canvasScale);
	canvasSprite.setPosition(m_canvasLeft * APP_WIDTH, m_canvasTop * APP_HEIGHT);

	m_screen->clear();

	m_colorGradingShader->setParameter("sCanvas", sf::Shader::CurrentTexture);
	m_colorGradingShader->setParameter("sTable", *m_colorGradingTable);

	m_screen->draw(canvasSprite, m_colorGradingShader);
	m_screen->display();
}
