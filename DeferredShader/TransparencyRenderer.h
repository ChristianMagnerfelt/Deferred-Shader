#pragma once

#include "Scene.h"
#include "Camera.h"
#include "ShaderManager.h"
#include "StateManager.h"

class TransparencyRenderer
{
	public:
		TransparencyRenderer(ShaderManager & shaderM, StateManager & stateM) 
			: shaderManager(shaderM), stateManager(stateM) {} 
		virtual void draw (Scene & scene, Camera & camera);
		virtual void drawLights(Scene & scene, Camera & camera);
	private:
		ShaderManager & shaderManager;
		StateManager & stateManager;
};