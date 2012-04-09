/**
@author: Christian Magnerfelt
@version: 2012.01.17
**/

#pragma once

#include "Util.h"
#include "DeferredShader.h"
#include "ContentManager.h"
#include "Scene.h"
#include "Camera.h"
#include "StateManager.h"
#include "TransparencyRenderer.h"

#define SCREEN_WIDTH	1280
#define SCREEN_HEIGHT	800


static const char *programName = "Deferred Shader";

void frwDisplay(void);
void frwReshape(GLsizei, GLsizei);
void frwKeyboard(unsigned char, int, int);
void frwIdle(void);
void frwMouseClick(int,int,int,int);
void frwMousemove(int,int);

class GlutWindow
{
	public:
		GlutWindow();
		~GlutWindow();
		void printGLInfo();
		void init(int & argc, char * argv []);
		void display();
		void reshape(GLsizei width, GLsizei height);
		void keyboard(unsigned char &, int &, int &);
		void idle();
		void run();
		void mouseClick(int button, int state, int x, int y);
		void mouseMove(int x, int y);
		void calculateFPS();
		void drawFPS();
	private:
		//  The number of frames
		int frameCount;

		//  Number of frames per second
		float fps;

		//  currentTime - previousTime is the time elapsed
		//  between every call of the Idle function
		int currentTime, previousTime;

		// Components
		Camera			camera;
		StateManager	stateManager;
		ShaderManager   shaderManager;
		DeferredShader	deferredShader;
		TransparencyRenderer transperencyRenderer;
		ContentManager	contentManager;
		Scene			scene;
};

static GlutWindow * gGlutWindow;