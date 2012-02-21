/**
@author: Christian Magnerfelt
@version: 2012.01.17
**/

#pragma once

// Standard Headers
#include "Util.h"

// Additional headers 
#include "TextureLoader.h"
#include "ModelLoader.h"

class ContentManager
{
	public:
		ContentManager();
		~ContentManager();
		TextureLoader & loadTexture();
		ModelLoader & loadModel();

	private:
		TextureLoader textureLoader;
		ModelLoader * modelLoader;
};