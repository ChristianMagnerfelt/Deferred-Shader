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
#include "StateHandler.h"

#include <iostream>

class DeferredShader
{
	public:
		DeferredShader();
		~DeferredShader();
		void init(GLuint screenWidth, GLuint screenHeight);
		void cleanUp();
		void draw(Scene & scene, Camera & camera, StateHandler & stateHandler);
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
		void debugStage(Camera & camera, StateHandler & stateHandler);

		//Lighting Stage
		void drawRec(Camera & camera);
		void drawLights();
		void lightingStage(Scene & scene, Camera & camera);
		void drawAmbient();
		void drawLighting(Scene & scene);
		int lightScissorTest(const Float3 & position, float radius, int sx, int sy, Camera & camera);

		//G-Buffers
		GLuint fbo;
		GLuint gbNormal;
		GLuint gbDepth;
		GLuint gbSpecular;
		GLuint gbDiffuse;
		GLuint screenHeight;
		GLuint screenWidth;
		GLboolean initOK;

		//Shader Manager
		ShaderManager	shaderManager;
};