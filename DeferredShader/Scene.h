/**
@author: Christian Magnerfelt
@version: 2012.01.17
**/

#pragma once

#include "Util.h"
#include "ContentManager.h"
#include "Model.h"
#include "ShaderManager.h"
#include "Light.h"

#include <vector>

typedef vector<Model*> ModelVector;
typedef vector<Light*> LightVector;

class Scene
{
	public:
		Scene();
		~Scene();
		void loadContent(ContentManager &);
		void draw(ShaderManager &);
		LightVector & getLightVector();
	private:
		ModelVector modelVector;
		LightVector lightVector;
};