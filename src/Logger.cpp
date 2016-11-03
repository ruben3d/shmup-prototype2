/*
 MIT License
 Copyright (c) 2016 Ruben Moreno Montoliu <ruben3d@gmail.com>
 */
//
// Logger.cpp - Created on 2016.06.11
//

#include "Logger.h"

#include <iostream>
#include "paths.h"

static const std::string LOG_FILE = "output.txt";

Logger *Logger::m_logger = NULL;

Logger *Logger::Get()
{
	if (!m_logger) m_logger = new Logger();
	return m_logger;
}

void Logger::Log(const std::string& text)
{
	Logger::Get()->log(text);
}

Logger::Logger()
{
	m_stream.open( buildFullPath(LOG_FILE), std::ios::out | std::ios::trunc );
}

Logger::~Logger()
{
	m_stream.close();
}

void Logger::log(const std::string& text)
{
	m_stream << text << std::endl;
	std::cout << text << std::endl;
}
