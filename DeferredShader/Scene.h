/**
@author: Christian Magnerfelt
@version: 2012.01.17
**/

#pragma once

#include "Util.h"
#include "ContentManager.h"
#include "Model.h"
#include "Camera.h"
#include "ShaderManager.h"
#include "Light.h"

#include <vector>

typedef std::vector<Model*> ModelVector;
typedef std::vector<Light*> LightVector;

class Scene
{
	public:
		Scene();
		~Scene();
		void loadContent(ContentManager &);
		void draw(ShaderManager &);
		void sortEntities(Camera & camera);
		LightVector & getLightVector();
	private:
		ModelVector modelVector;
		LightVector lightVector;
};

bool modelPositionCompare(Model * a, Model * b);