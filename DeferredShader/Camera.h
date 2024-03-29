/**
@author: Christian Magnerfelt
@version: 2012.01.17
**/

#pragma once

#include "Util.h"
#include <glm/glm.hpp>

static int count = 0;
class Camera
{
	public:
		Camera() : screenWidth(0), screenHeight(0) {}
		Camera(unsigned int width, unsigned int height) :  screenWidth(width), screenHeight(height){}

		// Camera Movement
		void moveCamera(float speed);
		void rotateView(float speed);
		void mouseMove();

		// Camera dimensions
		unsigned int getScreenHeight() const;
		unsigned int getScreenWidth() const;

		void setScreenHeight(const unsigned int height);
		void setScreenWidth(const unsigned int width);

		// Camera properties
		float getCameraSpeed();
		float getFieldOfView();
		float getAspectRatio();
		float getZNear();
		float getZFar();

		glm::vec3 getEyePoint();
		glm::vec3 getReferencePoint();
		glm::vec3 getUpVector();

		glm::mat4x4 getModelViewMatrix();
		glm::mat4x4 getProjectionMatrix();

		glm::vec3 getViewVector();

		//TODO: move mouse states to statehandler
		int getMouseX();
		int getMouseY();
		bool getFocus();

		void setCameraSpeed(const float speed);
		void setCameraPerspective(const float fieldOfView, const float aspectRation, const float zNear,const float zFar);
		void setCameraPosition(glm::vec3 eyePoint, glm::vec3 referencePoint, glm::vec3 upVector);

		void setFieldOfView(const float value);
		void setAspectRatio(const float value);
		void setZNear(const float value);
		void setZFar(const float value);

		void setEyePoint(const glm::vec3 vec);
		void setReferencePoint(const glm::vec3 vec);
		void setUpVector(const glm::vec3 vec);

		void setMouseX(const int x);
		void setMouseY(const int y);
		void setFocus(const bool value);

		// Set GL STACK
		void setGLModelView();
		void setGLProjection();		

		void calculatePlanes();
private:
		
		void calculateRVector();
		void calculateViewVector();

		// Camera variables
		float speed;
		// Perspective variables
		float fov;							// Field of view
		float aspect;						// Aspect ratio
		float near;							// Near clipping plane
		float far;							// Far clipping plane	
		// Viewport variables
		glm::vec3 eyeP;						// Eye Point
		glm::vec3 refP;						// Reference Point
		glm::vec3 upV;						// Up vector
		glm::mat4x4 modelViewMatrix;
		glm::mat4x4 projectionMatrix;
		
		// View vectors
		glm::vec3 rightV;					// Right vector
		glm::vec3 viewVec;
		glm::vec3 nearVec;
		glm::vec3 farVec;

		// Plane variables
		float hNear;
		float hFar;
		float wNear;
		float wFar;

		glm::vec3 nrb;						// Near right bottom
		glm::vec3 nrt;						// Near right top
		glm::vec3 nlb;						// Near left bottom
		glm::vec3 nlt;						// Near left top

		glm::vec3 frb;						// Far right bottom
		glm::vec3 frt;						// Far right top
		glm::vec3 flb;						// Far left bottom
		glm::vec3 flt;						// Far left top

		// Mouse variables 
		int mouseX;
		int mouseY;
		bool focus;

		// Screen dimensions
		unsigned int screenWidth;
		unsigned int screenHeight;
};