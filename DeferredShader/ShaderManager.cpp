#include "ShaderManager.h"

#include <iostream>

ShaderManager::~ShaderManager()
{
    cgDestroyProgram(cgGeometryStageVP);
    cgDestroyProgram(cgGeometryStageFP);
    cgDestroyContext(cgContext);
}
void ShaderManager::initShader()
{
	cgContext = cgCreateContext();
	checkForCgError("Creating Context");


	cgGLSetDebugMode(CG_FALSE);												// Debugging settings

	cgSetParameterSettingMode(cgContext, CG_IMMEDIATE_PARAMETER_SETTING);	// CG parameters will update immediately

	cgVertexProfile = cgGLGetLatestProfile(CG_GL_VERTEX);					// Get latest vertex profile
	cgGLSetOptimalOptions(cgVertexProfile);
	checkForCgError("Selecting Vertex Profile");

	cgGeometryStageVP = cgCreateProgramFromFile(
      cgContext,															// Cg runtime context
      CG_SOURCE,															// Program in human-readable form
      "GeometryStage.cg",													// Name of file containing program
      cgVertexProfile,														// Profile: OpenGL ARB vertex program
      "GeometryStageVS",													// Entry function name
      NULL);																// No extra compiler options
	checkForCgError("Creating Vertex Program From File");

	cgGLLoadProgram(cgGeometryStageVP);
	checkForCgError("Loading Vertex Program");

	// DEBUG
	cgDebugVP = cgCreateProgramFromFile(
      cgContext,															// Cg runtime context
      CG_SOURCE,															// Program in human-readable form
      "DebugDS.cg",															// Name of file containing program
      cgVertexProfile,														// Profile: OpenGL ARB vertex program
      "DebugVP",															// Entry function name
      NULL);																// No extra compiler options
	checkForCgError("Creating Vertex Program From File");

	cgGLLoadProgram(cgDebugVP);
	checkForCgError("Loading Vertex Program");

	cgFragmentProfile = cgGLGetLatestProfile(CG_GL_FRAGMENT);				// Get latest fragment profile
	cgGLSetOptimalOptions(cgFragmentProfile);
	checkForCgError("Selecting Fragment Profile");

	cgGeometryStageFP = cgCreateProgramFromFile(
		cgContext,									// Cg runtime context
		CG_SOURCE,									// Program in human-readable form
		"GeometryStage.cg",							// Name of file containing program
		cgFragmentProfile,							// Profile: OpenGL ARB vertex program
		"GeometryStageFS",							// Entry function name
		NULL);										// No extra compiler options
	checkForCgError("Creating Fragment Program From File");

	cgGLLoadProgram(cgGeometryStageFP);
	checkForCgError("Loading Fragment Program");

	cgDebugFP = cgCreateProgramFromFile(
		cgContext,									// Cg runtime context
		CG_SOURCE,									// Program in human-readable form
		"DebugDS.cg",								// Name of file containing program
		cgFragmentProfile,							// Profile: OpenGL ARB vertex program
		"DebugFP",									// Entry function name
		NULL);										// No extra compiler options
	checkForCgError("Creating Fragment Program From File");

	cgGLLoadProgram(cgDebugFP);
	checkForCgError("Loading Fragment Program");

	cgGLEnableProfile(cgVertexProfile);
	checkForCgError("Enabling Vertex Profile");

	cgGLEnableProfile(cgFragmentProfile);
	checkForCgError("Enabling Fragment Profile");
}
void ShaderManager::bindGeometryStageShader()
{
	cgGLBindProgram(cgGeometryStageVP);
	checkForCgError("Binding GS Vertex Program");

	cgGLBindProgram(cgGeometryStageFP);
	checkForCgError("Binding GS Fragment Program");
}
void ShaderManager::unbindGeometryStageShader()
{

}
void ShaderManager::bindLightingStageShader()
{

}
void ShaderManager::unbindLightingStageShader()
{

}
void ShaderManager::bindDebugShader()
{
	cgGLBindProgram(cgDebugVP);
	checkForCgError("Binding AS Vertex Program");

	cgGLBindProgram(cgDebugFP);
	checkForCgError("Binding AS Fragment Program");
}
void ShaderManager::updateModelviewMatrix()
{
	CGparameter modelviewMatrix;
	StateManager::renderingStage currentStage = stateManager.getRenderingStage();
	if(currentStage == StateManager::GEOMETRY_STAGE)
	{
		modelviewMatrix = cgGetNamedParameter(cgGeometryStageVP, "modelView");
	}
	cgGLSetStateMatrixParameter(modelviewMatrix, CG_GL_MODELVIEW_MATRIX, CG_GL_MATRIX_IDENTITY);
	checkForCgError("Setting Modelview Matrix");
}
void ShaderManager::updateModelviewPerspectiveMatrix()
{
	CGparameter modelviewProjMatrix;
	StateManager::renderingStage currentStage = stateManager.getRenderingStage();
	if(currentStage == StateManager::GEOMETRY_STAGE)
	{
		modelviewProjMatrix = cgGetNamedParameter(cgGeometryStageVP, "modelViewProj");
	}
	else if(currentStage == StateManager::DEBUG_STAGE)
	{
		modelviewProjMatrix = cgGetNamedParameter(cgDebugVP, "modelViewProj");
	}
	cgGLSetStateMatrixParameter(modelviewProjMatrix, CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);
	checkForCgError("Setting Modelview Projection Matrix");
}
void ShaderManager::bindCGParameter(CGparameter & parameter, const char * name)
{

}
bool ShaderManager::bindCGTexture(GLuint texID, TextureOptions options)
{
	CGparameter texture_param = nullptr;
	if(options == COLOR_TEXTURE)
	{
		texture_param = cgGetNamedParameter(cgGeometryStageFP, "colorTex");
		checkForCgError("Getting Texture Parameter");
	}
	else if(options == NORMAL_TEXTURE)
	{
		texture_param = cgGetNamedParameter(cgGeometryStageFP, "normalTex");
		checkForCgError("Getting Texture Parameter");
	}
	else if(options == GB_DEBUG)
	{
		texture_param = cgGetNamedParameter(cgDebugFP, "gbTex");
		checkForCgError("Getting Texture Parameter");
	}
	else
	{
		std::cout << "Invalid parameter configuration" << std::endl;
		return false;
	}
	cgGLSetTextureParameter(texture_param, texID);
	cgGLEnableTextureParameter(texture_param);
	checkForCgError("Setting 2D Texture ");
	return true;
}
bool ShaderManager::setCgParam(float value, const char * name, Shader shader)
{
	CGparameter param = getParamFromShader(name,shader);
	if(param != nullptr) 
	{
		cgGLSetParameter1f(param, value);
		checkForCgError("Setting Material");
		return true;
	}
	return false;
}
bool  ShaderManager::setCgParam(glm::vec3 vec, const char * name, Shader shader)
{
	CGparameter param = getParamFromShader(name,shader);
	if(param != nullptr) ;
	{
		cgGLSetParameter3f(param, vec.r, vec.g, vec.b);
		checkForCgError("Setting Material");
		return true;
	}
	return false;
}
CGparameter ShaderManager::getParamFromShader(const char * name, Shader & shader)
{
	CGparameter param = nullptr;
	// TODO: function map to add scalibility of setting params for shaders
	StateManager::renderingStage currentStage = stateManager.getRenderingStage();
	if(currentStage == StateManager::GEOMETRY_STAGE && shader == VERTEX)
	{
		param = cgGetNamedParameter(cgGeometryStageVP, name);
		checkForCgError(name);
	}
	else if(currentStage == StateManager::GEOMETRY_STAGE && shader == FRAGMENT)
	{
		param = cgGetNamedParameter(cgGeometryStageFP, name);
		checkForCgError(name);
	}
	else if(currentStage == StateManager::LIGHTING_STAGE && shader == VERTEX)
	{
		param = cgGetNamedParameter(cgLightingStageVP, name);
		checkForCgError(name);
	}
	else if(currentStage == StateManager::LIGHTING_STAGE && shader == FRAGMENT)
	{
		param = cgGetNamedParameter(cgLightingStageFP, name);
		checkForCgError(name);
	}
	else
	{
		std::cout << "Invalid parameter configuration" << std::endl;
	}
	return param;
}
void ShaderManager::checkForCgError(const char * situation)
{
	CGerror error;
	const char *string = cgGetLastErrorString(&error);

	if (error != CG_NO_ERROR) 
	{
		std::cerr << programName << " : " << situation << " : " << string << std::endl;
		if (error == CG_COMPILER_ERROR) 
		{
			std::cerr << cgGetLastListing(cgContext) << std::endl;
		}
		system("pause");
		exit(1);
  }
}