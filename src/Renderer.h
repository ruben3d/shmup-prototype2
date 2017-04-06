/*
 MIT License
 Copyright (c) 2016 Ruben Moreno Montoliu <ruben3d@gmail.com>
 */
//
// Renderer.h - Created on 2016.06.07
//

#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <string>
#include <SFML/Graphics.hpp>

class Application;
class Scene;
class Tile;
class Camera;
class Light;
class MaterialPrototype;
class Entity;

class Renderer
{
public:
	static const int CANVAS_WIDTH;
	static const int CANVAS_HEIGHT;

	Renderer(sf::RenderWindow *renderWindow, const int appWidth, const int appHeight);
	~Renderer();

	void render(const Scene *scene);

private:
	Renderer(const Renderer&);

	const int APP_WIDTH;
	const int APP_HEIGHT;

	// Position of the canvas in the screen from top, [0,1]
	float m_canvasTop;
	// Position of the canvas in the screen from left, [0,1]
	float m_canvasLeft;
	// Scale factor for the canvas to fill the screen, maintaining aspect ratio, leaving black bars if necessary. [1,...)
	float m_canvasScale;

	sf::RenderWindow *m_screen;
	sf::RenderTexture *m_canvas;

	sf::Shader *m_colorGradingShader;
	sf::Texture *m_colorGradingTable;

	sf::Shader *m_tileBaseShader;
	sf::Shader *m_tileBaseEmissionShader;
	sf::Shader *m_tileLightOmniShader;

	int computeCanvasSizeMultiplier() const;
	sf::RenderTexture *createCanvas(const int canvasSizeMultiplier) const;
	void setCanvasDisplaySettings(const int canvasSizeMultiplier);
	sf::Shader *createShader(const std::string& verterShader, const std::string& fragmentShader);
	sf::Texture *createColorGradingTable();

	const sf::View createGameView(const Scene *scene) const;
	void renderLevel(const Scene *scene);
	void renderTileBase(const Scene *scene);
	void renderSpriteBase(const Scene *scene, const sf::Sprite& sprite, const MaterialPrototype *prototype);
	bool hasLights(const Scene *scene);
	void renderTileLights(const Scene *scene);
	bool isLightOnCamera(const Camera *camera, const Light *light);
	void renderLightTiles(const Scene *scene, const Light *light);
	void renderSpriteLight(const sf::Sprite& sprite, const MaterialPrototype *prototype, const Light *light);
	void renderEntities(const Scene *scene);
	void renderEntity(const Scene *scene, const Entity *entity);
	void renderEntityLights(const Scene *scene, const Entity *entity);
	void renderEntityLight(const Scene *scene, const Entity *entity, const Light *light);
	bool isEntityLighted(const float top, const float bottom, const float left, const float right, const Entity* entity);
	void renderCanvasToScreen();
};

#endif /* _RENDERER_H_ */
