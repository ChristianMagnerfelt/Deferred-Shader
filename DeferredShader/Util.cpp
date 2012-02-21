#include "Util.h"

#include <iostream>

void checkFramebufferEXTSupport()
{
	if (GLEW_EXT_framebuffer_object)
	{
		cout << "FBO EXT Supported" << endl;
	}
	else
	{
		cerr << "FBO EXT is not supported" << endl;
		//system("pause");
		//system("exit");
	}
}
void checkFramebufferStatus(){
	GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	switch(status)
	{
		case GL_FRAMEBUFFER_COMPLETE_EXT:
			//GBuffer bind OK
			break;
		case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
			cerr << "FBO Error : Framebuffer configuration not supported" << endl;
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
			cerr << "FBO Error : Incomplete attachment" << endl;
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
			cerr << "FBO Error : Incomplete missing attachment" << endl;
			break;
		default:
			//Error
			cerr << "FBO Error : " << status << endl;
	}
}

void checkGLErrors(const char * action)
{
	GLenum status = glGetError();
	switch(status)
	{
		case GL_NO_ERROR:
			// OK
			break;
		case GL_INVALID_ENUM:
			cerr << action << " : An unacceptable value is specified for an enumerated argument" << endl;
			break;
		case GL_INVALID_OPERATION:
			cerr << action << " : The specified operation is not allowed in the current state" << endl;
			break;
		case GL_STACK_OVERFLOW:
			cerr << action << " : Stack Overflow" << endl;
			break;
		default:
			cerr << action << " : GL error " << status << endl;
	}

}