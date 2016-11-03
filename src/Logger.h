/*
 MIT License
 Copyright (c) 2016 Ruben Moreno Montoliu <ruben3d@gmail.com>
 */
//
// Logger.h - Created on 2016.06.11
//

#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <fstream>
#include <string>

#define LOG(msg) Logger::Log(msg);

class Logger
{
public:
	static Logger *Get();
	static void Log(const std::string& text);

	~Logger();

	void log(const std::string& text);

private:
	static Logger *m_logger;
	std::ofstream m_stream;

	Logger();
};

#endif /* _LOGGER_H_ */
