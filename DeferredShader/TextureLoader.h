/**
@author: Christian Magnerfelt
@version: 2012.01.17
**/

#pragma once

#include "Util.h"

#include <fstream>

class TextureLoader
{
	public:
		GLuint loadJPGTexture(const char * fileName);
		GLuint loadRAWRGBTexture(const char * fileName, int width, int height);
	private:
};