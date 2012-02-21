#include "Camera.h"

#include <iostream>
void Camera::setCameraPerspective(float fieldOfView, float aspectRation, float zNear, float zFar)
{
	fov = fieldOfView;
	aspect = aspectRation;
	near = zNear;
	far = zFar;
}
void Camera::setCameraPosition(Float3 eyePoint, Float3 referencePoint, Float3 upVector)
{
	eyeP = eyePoint;
	refP = referencePoint;
	upV = upVector;
}
void Camera::setCameraSpeed(float s)
{
	speed = s;
}
void Camera::moveCamera(float speed)
{
	Float3 vVector = Float3(refP.x-eyeP.x, refP.y-eyeP.y, refP.z-eyeP.z);	// Calculate view vector

	eyeP.x  = eyeP.x  + vVector.x * speed;
	eyeP.z  = eyeP.z  + vVector.z * speed;
	refP.x = refP.x + vVector.x * speed;
	refP.z = refP.z + vVector.z * speed;
}
void Camera::rotateView(float speed)
{
	Float3 vVector = Float3(refP.x-eyeP.x, refP.y-eyeP.y, refP.z-eyeP.z);	// Calculate view vector

	refP.z = (float)(eyeP.z + sin(speed)*vVector.x + cos(speed)*vVector.z);
	refP.x = (float)(eyeP.x + cos(speed)*vVector.x - sin(speed)*vVector.z);
}
void Camera::mouseMove(int width, int height)
{

	int mid_x = width/2;	
	int mid_y = height/2;	
	float angle_y  = 0.0f;				
	float angle_z  = 0.0f;												
	
	if( (mouseX == mid_x) && (mouseY == mid_y) ) return;

	glutWarpPointer(width/2, height/2);	// Set the mouse cursor in the center of the window						

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
void Camera::setGLModelView()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		eyeP.x,
		eyeP.y,
		eyeP.z,
		refP.x,
		refP.y,
		refP.z,
		upV.x,
		upV.y,
		upV.z);
}
void Camera::setGLProjection()
{
	glMatrixMode(GL_PROJECTION);	
	glLoadIdentity();
	gluPerspective(
		fov,
		aspect,
		near,
		far);
}