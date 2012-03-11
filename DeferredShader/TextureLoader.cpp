#include "TextureLoader.h"

#include <iostream>

GLuint TextureLoader::loadJPGTexture(const char * fileName)
{
	//NOT IMPLEMENTED
	return 0;
}
GLuint TextureLoader::loadRAWRGBTexture(const char * fileName, int width, int height)
{
	std::cout << "Reading RAW texture : " << fileName << std::endl;
	GLuint text;
    char * buffer;
	int length = width * height * 3;
	
	std::ifstream is;
	is.open(fileName, std::ios::binary);				// Open texture data

	buffer = new char [length];					// Allocate buffer

	is.read (buffer,length);					// Read texture data
	is.close();

	glGenTextures(1, &text);					// Generate texture
	glBindTexture(GL_TEXTURE_2D, text);
	glTexParameteri(GL_TEXTURE_2D, 
		GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, 
		GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 
		width, height, 0,GL_RGB, 
		GL_UNSIGNED_BYTE, buffer);

	delete [] buffer;							// Delete buffer
	std::cout << "Loaded RAW texture : " << fileName << " : Texture ID : " << text << std::endl;
    return text;
}