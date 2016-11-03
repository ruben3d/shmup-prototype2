/*
 MIT License
 Copyright (c) 2016 Ruben Moreno Montoliu <ruben3d@gmail.com>
 */
//
// Application.cpp - Created on 2016.06.07
//

#include "Application.h"

#include "config.h"

Application::Application()
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	m_width = desktop.width;
	m_height = desktop.height;

	initHistory();

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	m_window = new sf::RenderWindow(sf::VideoMode(m_width, m_height), APPLICATION_NAME, sf::Style::None /*sf::Style::Titlebar|sf::Style::Close*/ /*sf::Style::Fullscreen*/, settings);
	//m_window = new sf::RenderWindow(sf::VideoMode(m_width, m_height), APPLICATION_NAME, sf::Style::Titlebar|sf::Style::Close, settings);
	m_window->setVerticalSyncEnabled(false);
	m_window->setPosition(sf::Vector2i(desktop.width/2-m_width/2, desktop.height/2-m_height/2));
}

Application::~Application()
{
	delete m_window;
}

void Application::initHistory()
{
	for (int i=0; i<HISTORY_SIZE; i++)
	{
		m_history[i] = 1.0f/60.0f;
	}
}

float Application::updateAndGetDelta(float delta)
{
	m_history[m_historyCursor++] = delta;
	m_historyCursor %= HISTORY_SIZE;

	float total = 0;
	for (int i=0; i<HISTORY_SIZE; i++)
	{
		total += m_history[i];
	}

	return total / HISTORY_SIZE;
}

float Application::startFrame()
{
	return updateAndGetDelta(m_clock.restart().asSeconds());
}

bool Application::isOpen() const
{
	return m_window->isOpen();
}

bool Application::close()
{
	m_window->close();
}

bool Application::pollEvent(sf::Event& event)
{
	return m_window->pollEvent(event);
}
