#include "Util.h"

#include <iostream>

void checkFramebufferEXTSupport()
{
	if (GLEW_EXT_framebuffer_object)
	{
		std::cout << "FBO EXT Supported" << std::endl;
	}
	else
	{
		std::cerr << "FBO EXT is not supported" << std::endl;
		//system("pause");
		//system("exit");
	}
}
void checkVertexBufferEXTSupport()
{
	if (GLEW_ARB_vertex_buffer_object)
	{
		std::cout << "VBO EXT Supported" << std::endl;
	}
	else
	{
		std::cerr << "VBO EXT is not supported" << std::endl;
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
			std::cerr << "FBO Error : Framebuffer configuration not supported" << std::endl;
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
			std::cerr << "FBO Error : Incomplete attachment" << std::endl;
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
			std::cerr << "FBO Error : Incomplete missing attachment" << std::endl;
			break;
		default:
			//Error
			std::cerr << "FBO Error : " << status << std::endl;
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
			std::cerr << action << " : An unacceptable value is specified for an enumerated argument" << std::endl;
			break;
		case GL_INVALID_OPERATION:
			std::cerr << action << " : The specified operation is not allowed in the current state" << std::endl;
			break;
		case GL_STACK_OVERFLOW:
			std::cerr << action << " : Stack Overflow" << std::endl;
			break;
		default:
			std::cerr << action << " : GL error " << status << std::endl;
	}

}