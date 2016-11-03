/*
 MIT License
 Copyright (c) 2016 Ruben Moreno Montoliu <ruben3d@gmail.com>
 */
//
// paths.cpp - Created on 2016.06.04
//

#include "paths.h"
#include "config.h"

std::string buildFullPath(const std::string relativePath)
{
	std::string fullPath;
	fullPath += APPLICATION_PATH_DATA;
	fullPath += PATH_SEPARATOR;
	fullPath += relativePath;
	return fullPath;
}
