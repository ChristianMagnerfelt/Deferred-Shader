#include "Camera.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

void Camera::moveCamera(float speed)
{
	calculateViewVector();

	eyeP.x  = eyeP.x  + viewVec.x * speed;
	eyeP.z  = eyeP.z  + viewVec.z * speed;
	refP.x = refP.x + viewVec.x * speed;
	refP.z = refP.z + viewVec.z * speed;
}
void Camera::rotateView(float speed)
{
	calculateViewVector();

	refP.z = (float)(eyeP.z + sin(speed)*viewVec.x + cos(speed)*viewVec.z);
	refP.x = (float)(eyeP.x + cos(speed)*viewVec.x - sin(speed)*viewVec.z);
}
void Camera::mouseMove()
{
	if(focus)
	{
		int mid_x = screenWidth/2;	
		int mid_y = screenHeight/2;	
		float angle_y  = 0.0f;				
		float angle_z  = 0.0f;												
		
		if( (mouseX == mid_x) && (mouseY == mid_y) ) return;
		
		glutWarpPointer(mid_x, mid_y);	// Set the mouse cursor in the center of the window						

		// Get the direction from the mouse cursor, set a resonable maneuvering speed
		angle_y = (float)( (mid_x - mouseX) ) / 1000;		
		angle_z = (float)( (mid_y - mouseY) ) / 1000;

		// The higher the value is the faster the camera looks around.
		refP.y += angle_z * 10;

		// limit the rotation around the x-axis
		if((refP.y - eyeP.y) > 8)  refP.y = eyeP.y + 8;
		if((refP.y - eyeP.y) <-8)  refP.y = eyeP.y - 8;
	
		rotateView(-angle_y); // Rotate
	}
}
// Camera dimensions
unsigned int Camera::getScreenWidth() const
{
	return screenWidth;
}
unsigned int Camera::getScreenHeight() const
{
	return screenHeight;
}
void Camera::setScreenHeight(const unsigned int height)
{
	screenHeight = height;
}
void Camera::setScreenWidth(const unsigned int width)
{
	screenWidth = width;
}
// Camera properties
float Camera::getCameraSpeed()
{
	return speed;
}
float Camera::getFieldOfView()
{
	return fov;
}
float Camera::getAspectRatio()
{
	return aspect;
}
float Camera::getZNear()
{
	return near;
}
float Camera::getZFar()
{
	return far;
}
glm::vec3 Camera::getEyePoint()
{
	return eyeP;
}
glm::vec3 Camera::getReferencePoint()
{
	return refP;
}
glm::vec3 Camera::getUpVector()
{
	return upV;
}
glm::mat4x4 Camera::getModelViewMatrix()
{
	return modelViewMatrix;
}
glm::mat4x4 Camera::getProjectionMatrix()
{
	return projectionMatrix;
}
glm::vec3 Camera::getViewVector()
{
	return viewVec;
}
int Camera::getMouseX()
{
	return mouseX;
}
int Camera::getMouseY()
{
	return mouseY;
}
bool Camera::getFocus()
{
	return focus;
}
void Camera::setCameraSpeed(const float cameraSpeed)
{
	speed = cameraSpeed;
}
void Camera::setCameraPerspective(const float fieldOfView, const float aspectRation, const float zNear, const float zFar)
{
	fov = fieldOfView;
	aspect = aspectRation;
	near = zNear;
	far = zFar;
}
void Camera::setCameraPosition(const glm::vec3 eyePoint, const glm::vec3 referencePoint, const glm::vec3 upVector)
{
	eyeP = eyePoint;
	refP = referencePoint;
	upV = upVector;
}
void Camera::setFieldOfView(const float fieldOfView)
{
	fov = fieldOfView;
}
void Camera::setAspectRatio(const float aspectRatio)
{
	aspect = aspectRatio;
}
void Camera::setZNear(const float zNear)
{
	near = zNear;
}
void Camera::setZFar(const float zFar)
{
	far = zFar;
}
void Camera::setEyePoint(const glm::vec3 eyePoint)
{
	eyeP = eyePoint;
	//calculateRVector();
}
void Camera::setReferencePoint(const glm::vec3 referencePoint)
{
	refP = referencePoint;
	//calculateRVector();
}
void Camera::setUpVector(const glm::vec3 upVector)
{
	upV = upVector;
	//calculateRVector();
}
void Camera::setMouseX(int x)
{
	mouseX = x;
}
void Camera::setMouseY(int y)
{
	mouseY = y;
}
void Camera::setFocus(const bool value)
{
	focus = value;
}
void Camera::setGLModelView()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	modelViewMatrix = glm::lookAt(eyeP,refP,upV);
	glLoadMatrixf(&modelViewMatrix[0][0]);
	checkGLErrors("Setting modelview matrix");
}
void Camera::setGLProjection()
{
	glMatrixMode(GL_PROJECTION);	
	glLoadIdentity();
	projectionMatrix = glm::perspective(fov,aspect,near,far);
	glLoadMatrixf(&projectionMatrix[0][0]);
	checkGLErrors("Setting projection matrix");
}
void Camera::calculatePlanes()
{
	calculateViewVector();

	nearVec = eyeP + near * viewVec;
	farVec = eyeP + far * viewVec;

	hNear = near * tan(fov);
	hFar = far * tan(fov);
	wNear = hNear * aspect;
	wFar = hFar * aspect;
	
	calculateRVector();

	nrb = nearVec - hNear*upV + wNear*rightV;
	nrt = nearVec + hNear*upV + wNear*rightV;
	nlb = nearVec - hNear*upV - wNear*rightV;
	nlt = nearVec + hNear*upV - wNear*rightV;

	frb = farVec - hFar*upV + wFar*rightV;
	frt = farVec + hFar*upV + wFar*rightV;
	flb = farVec - hFar*upV - wFar*rightV;
	flt = farVec + hFar*upV - wFar*rightV;

	
}
void Camera::calculateRVector()
{
	rightV = glm::normalize(glm::cross((refP - eyeP),upV));
}
void Camera::calculateViewVector()
{
	viewVec = refP - eyeP;
}