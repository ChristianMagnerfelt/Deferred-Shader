#include "ContentManager.h"

ContentManager::ContentManager()
{
	modelLoader = new ModelLoader();
}

ContentManager::~ContentManager()
{
	delete modelLoader;
}

TextureLoader & ContentManager::loadTexture()
{
	return textureLoader;
}

ModelLoader & ContentManager::loadModel()
{
	return *modelLoader;
}