/**
@author: Christian Magnerfelt
@version: 2012.01.17

Deferred Shader


**/

#pragma once

#include "Util.h"
#include "ShaderManager.h"
#include "Scene.h"
#include "Camera.h"
#include "StateManager.h"

#include <iostream>

class DeferredShader
{
	public:
		DeferredShader(StateManager & stateM, ShaderManager & shaderM);
		~DeferredShader();
		void init(Camera & camera);
		void cleanUp();
		void draw(Scene & scene, Camera & camera);
	private:
		//G-Buffer management
		void bindGBuffer();
		void unbindGBuffer();
	
		//P-Buffer management
		void bindPBuffer();
		void unbindPBuffer();

		//Geometry Stage
		void geometryStage(Scene & scene,Camera & camera);

		//Debug Stage
		void debugStage(Camera & camera);

		//Lighting Stage
		void drawRec(Camera & camera);
		void drawLights();
		void lightingStage(Scene & scene, Camera & camera);
		void drawAmbient();
		void drawLighting(Scene & scene, Camera & camera);
		int lightScissorTest(const glm::vec3 & position, float radius, int sx, int sy, Camera & camera);

		//G-Buffers
		GLuint fbo;
		GLuint gbNormal;
		GLuint gbDepth;
		GLuint gbSpecular;
		GLuint gbDiffuse;

		//Shader Manager
		ShaderManager & shaderManager;
		StateManager & stateManager;
};