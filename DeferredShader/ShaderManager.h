/**
@author: Christian Magnerfelt
@version: 2012.01.17
**/

#pragma once 

#include "Util.h"
#include "StateManager.h"

#include <glm\glm.hpp>
#include <string>

//TODO: Shadow & light textures
enum TextureOptions {
	COLOR_TEXTURE,
	NORMAL_TEXTURE,
	GB_DEBUG
};

// TODO: format for scalability of multiple shaders per stage
enum Shader {
	VERTEX,
	FRAGMENT,
};

class ShaderManager 
{
	public:
		ShaderManager(StateManager & manager) : stateManager(manager), programName("DS ShaderManager") {}
		~ShaderManager();
		void initShader();

		void bindGeometryStageShader();
		void unbindGeometryStageShader();
		void bindDebugShader();
		void bindLightingStageShader();
		void unbindLightingStageShader();

		void updateModelviewMatrix();
		void updateModelviewPerspectiveMatrix();

		void bindCGParameter(CGparameter & parameter, const char * name);
		bool bindCGTexture(GLuint texID, TextureOptions);
		bool setCgParam(float value, const char * name, Shader shader);
		bool setCgParam(glm::vec3 vec, const char * name, Shader shader);
	
	private:
		CGparameter getParamFromShader(const char * name, Shader & shader);

		void checkForCgError(const char * situation);

		CGcontext cgContext;
		CGprofile cgVertexProfile, cgFragmentProfile;
		CGprogram cgGeometryStageVP, cgGeometryStageFP, cgLightingStageVP, cgLightingStageFP, cgDebugVP, cgDebugFP;
		const char * programName;
		StateManager & stateManager;
};