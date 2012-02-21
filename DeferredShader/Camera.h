/**
@author: Christian Magnerfelt
@version: 2012.01.17
**/

#pragma once

#include "Util.h"


class Camera
{
	public:
		Camera(){}
		void setCameraPerspective(float fieldOfView, float aspectRation, float zNear, float zFar);
		void setCameraPosition(Float3 eyePoint, Float3 referencePoint, Float3 upVector);
		void setCameraSpeed(float speed);

		// Set GL STACK
		void setGLModelView();
		void setGLProjection();

		// Camera Movement
		void moveCamera(float speed);
		void rotateView(float speed);
		void mouseMove(int width, int height);

		// Camera variables
		float speed;
		// Perspective variables
		float fov;							// Field of view
		float aspect;						// Aspect ratio
		float near;							// Near clipping plane
		float far;							// Far clipping plane	
		// Viewport variables
		Float3 eyeP;						// Eye Point
		Float3 refP;						// Reference Point
		Float3 upV;							// Up vector
		// Mouse variables 
		int mouseX;
		int mouseY;
};