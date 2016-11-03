/*
 MIT License
 Copyright (c) 2016 Ruben Moreno Montoliu <ruben3d@gmail.com>
 */
//
// Application.h - Created on 2016.06.07
//

#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <SFML/Graphics.hpp>
#include "Renderer.h"

class Application
{
public:
	Application();
	~Application();

	float getWidth() const {return m_width;}
	float getHeight() const {return m_height;}

	float startFrame();

	bool isOpen() const;
	bool close();
	bool pollEvent(sf::Event& event);

private:
	Application(const Application&);

	// To get the window handle without exposing it on the public API
	friend Renderer::Renderer(Application *application);
	sf::RenderWindow *getWindow() {return m_window;}

	constexpr static unsigned int HISTORY_SIZE = 8;
	float m_history[HISTORY_SIZE];
	int m_historyCursor = 0;

	int m_width;
	int m_height;

	sf::RenderWindow *m_window;
	sf::Clock m_clock;

	void initHistory();
	float updateAndGetDelta(float delta);
};

#endif /* _APPLICATION_H_ */
