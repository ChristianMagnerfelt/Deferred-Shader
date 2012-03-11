/**
@author: Christian Magnerfelt
@version: 2012.01.17
**/

#pragma once

// OpenGL
#include <GL/glew.h>
#include <GL/glut.h>

// Cg
#include <Cg/cg.h>
#include <Cg/cgGL.h>

// C Headers
#include <cstdlib>
#include <cstddef>

// Additional headers
#include <utility>

// Add libraries
#pragma comment (lib , "cg.lib")
#pragma comment (lib , "cgGL.lib")
#pragma comment (lib , "glut32.lib")
#pragma comment (lib , "glew32.lib")
#pragma comment (lib , "assimp.lib")

/** Typedefs
typedef std::pair<float,float> Float2;

struct Float3
{
	Float3() : x(0.0), y(0.0), z(0.0){}
	Float3(float a,float b,float c) : x(a), y(b), z(c){}
	float x,y,z;
	Float3 dot(Float3 fl){ return Float3(x*fl.x,y*fl.y,z*fl.z);}
};

struct Float4
{
	Float4() : x(0.0), y(0.0), z(0.0), w(0.0){}
	Float4(float a,float b,float c,float d) : x(a), y(b), z(c), w(d){}
	float x,y,z,w;
	Float4 dot(const Float4 & fl){ return Float4(x*fl.x,y*fl.y,z*fl.z,w*fl.w);}
};**/

// Debugging
void checkFramebufferEXTSupport();
void checkVertexBufferEXTSupport();
void checkFramebufferStatus();
void checkGLErrors(const char * action);

