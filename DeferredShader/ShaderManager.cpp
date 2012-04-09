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

	// Get latest vertex profile
	cgVertexProfile = cgGLGetLatestProfile(CG_GL_VERTEX);					
	cgGLSetOptimalOptions(cgVertexProfile);
	checkForCgError("Selecting Vertex Profile");

	// Geometry stage vertex program
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

	// Debug stage vertex program
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

	// Lighting stage vertex program
	cgLightingStageVP = cgCreateProgramFromFile(
      cgContext,															// Cg runtime context
      CG_SOURCE,															// Program in human-readable form
      "LightingStage.cg",													// Name of file containing program
      cgVertexProfile,														// Profile: OpenGL ARB vertex program
      "LightingStageVP",													// Entry function name
      NULL);																// No extra compiler options
	checkForCgError("Creating Lighting Stage Vertex Program From File");

	cgGLLoadProgram(cgLightingStageVP);
	checkForCgError("Loading Lighting Stage Vertex Program");

	// Transparency stage vertex program
	cgTransparencyStageVP = cgCreateProgramFromFile(
      cgContext,															// Cg runtime context
      CG_SOURCE,															// Program in human-readable form
      "TransparencyStage.cg",													// Name of file containing program
      cgVertexProfile,														// Profile: OpenGL ARB vertex program
      "TransparencyStageVP",													// Entry function name
      NULL);																// No extra compiler options
	checkForCgError("Creating Transparency Stage Vertex Program From File");

	cgGLLoadProgram(cgTransparencyStageVP);
	checkForCgError("Loading Transparency Stage Vertex Program");

	// Get latest fragment profile
	cgFragmentProfile = cgGLGetLatestProfile(CG_GL_FRAGMENT);				
	cgGLSetOptimalOptions(cgFragmentProfile);
	checkForCgError("Selecting Fragment Profile");

	// Geometry stage fragment program
	cgGeometryStageFP = cgCreateProgramFromFile(
		cgContext,															// Cg runtime context
		CG_SOURCE,															// Program in human-readable form
		"GeometryStage.cg",													// Name of file containing program
		cgFragmentProfile,													// Profile: OpenGL ARB vertex program
		"GeometryStageFS",													// Entry function name
		NULL);																// No extra compiler options
	checkForCgError("Creating Fragment Program From File");

	cgGLLoadProgram(cgGeometryStageFP);
	checkForCgError("Loading Fragment Program");

	// Debug stage fragment program
	cgDebugFP = cgCreateProgramFromFile(
		cgContext,															// Cg runtime context
		CG_SOURCE,															// Program in human-readable form
		"DebugDS.cg",														// Name of file containing program
		cgFragmentProfile,													// Profile: OpenGL ARB vertex program
		"DebugFP",															// Entry function name
		NULL);																// No extra compiler options
	checkForCgError("Creating Fragment Program From File");

	cgGLLoadProgram(cgDebugFP);
	checkForCgError("Loading Fragment Program");

	// Lighting stage fragment program
	cgLightingStageFP = cgCreateProgramFromFile(
		cgContext,															// Cg runtime context
		CG_SOURCE,															// Program in human-readable form
		"LightingStage.cg",													// Name of file containing program
		cgFragmentProfile,													// Profile: OpenGL ARB vertex program
		"LightingStageFP",													// Entry function name
		NULL);																// No extra compiler options
	checkForCgError("Creating Lighting Stage Fragment Program From File");

	cgGLLoadProgram(cgLightingStageFP);
	checkForCgError("Loading Lighting Stage Fragment Program");

	// Transparency stage fragment program
	cgTransparencyStageFP = cgCreateProgramFromFile(
		cgContext,															// Cg runtime context
		CG_SOURCE,															// Program in human-readable form
		"TransparencyStage.cg",													// Name of file containing program
		cgFragmentProfile,													// Profile: OpenGL ARB vertex program
		"TransparencyStageFP",													// Entry function name
		NULL);																// No extra compiler options
	checkForCgError("Creating Transparency Stage Fragment Program From File");

	cgGLLoadProgram(cgTransparencyStageFP);
	checkForCgError("Loading Transparency Stage Fragment Program");

	// Enable profiles
	cgGLEnableProfile(cgVertexProfile);
	checkForCgError("Enabling Vertex Profile");

	cgGLEnableProfile(cgFragmentProfile);
	checkForCgError("Enabling Fragment Profile");
}
void ShaderManager::bindStageShader()
{
	switch(stateManager.getRenderingStage())
	{
		case (StateManager::GEOMETRY_STAGE) :
			cgGLBindProgram(cgGeometryStageVP);
			checkForCgError("Binding GS Vertex Program");
			cgGLBindProgram(cgGeometryStageFP);
			checkForCgError("Binding GS Fragment Program");
			break;
		case (StateManager::LIGHTING_STAGE) :
			cgGLBindProgram(cgLightingStageVP);
			checkForCgError("Binding GS Vertex Program");
			cgGLBindProgram(cgLightingStageFP);
			checkForCgError("Binding GS Fragment Program");
			break;
		case (StateManager::DEBUG_STAGE) :
			cgGLBindProgram(cgDebugVP);
			checkForCgError("Binding AS Vertex Program");
			cgGLBindProgram(cgDebugFP);
			checkForCgError("Binding AS Fragment Program");
			break;
		case (StateManager::TRANSPARENCY_STAGE) :
			cgGLBindProgram(cgTransparencyStageVP);
			checkForCgError("Binding Transparency stage vertex program");
			cgGLBindProgram(cgTransparencyStageFP);
			checkForCgError("Binding Transparency stage fragment program");
			break;
		default :
			break;
	}
}
void ShaderManager::updateModelviewMatrix()
{
	CGparameter modelviewMatrix;
	StateManager::renderingStage currentStage = stateManager.getRenderingStage();
	if(currentStage == StateManager::GEOMETRY_STAGE)
	{
		modelviewMatrix = cgGetNamedParameter(cgGeometryStageVP, "modelView");
	}
	else
	{
		return;
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
	else if(currentStage == StateManager::LIGHTING_STAGE)
	{
		modelviewProjMatrix = cgGetNamedParameter(cgLightingStageVP, "modelViewProj");
	}
	else if(currentStage == StateManager::TRANSPARENCY_STAGE)
	{
		modelviewProjMatrix = cgGetNamedParameter(cgTransparencyStageVP, "modelViewProj");
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
		if(stateManager.getRenderingStage() == StateManager::GEOMETRY_STAGE)
		{
			texture_param = cgGetNamedParameter(cgGeometryStageFP, "colorTex");
			checkForCgError("Getting Texture Parameter");
		}
		else if(stateManager.getRenderingStage() == StateManager::TRANSPARENCY_STAGE)
		{
			texture_param = cgGetNamedParameter(cgTransparencyStageFP, "colorTex");
			checkForCgError("Getting Texture Parameter");
		}
	}
	else if(options == NORMAL_TEXTURE)
	{
		if(stateManager.getRenderingStage() == StateManager::GEOMETRY_STAGE)
		{
			texture_param = cgGetNamedParameter(cgGeometryStageFP, "normalTex");
			checkForCgError("Getting Texture Parameter");
		}
		else if(stateManager.getRenderingStage() == StateManager::TRANSPARENCY_STAGE)
		{
			texture_param = cgGetNamedParameter(cgTransparencyStageFP, "normalTex");
			checkForCgError("Getting Texture Parameter");
		}
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
bool ShaderManager::setCgParam(GLuint id, const char * name, Shader shader)
{
	CGparameter param = getParamFromShader(name,shader);
	if(param != nullptr) 
	{
		cgGLSetTextureParameter(param, id);
		cgGLEnableTextureParameter(param);
		checkForCgError("Setting Texture");
		return true;
	}
	return false;
}
bool ShaderManager::setCgParam(float value, const char * name, Shader shader)
{
	CGparameter param = getParamFromShader(name,shader);
	if(param != nullptr) 
	{
		cgGLSetParameter1f(param, value);
		checkForCgError("Setting parameter");
		return true;
	}
	return false;
}
bool  ShaderManager::setCgParam(glm::vec3 vec, const char * name, Shader shader)
{
	CGparameter param = getParamFromShader(name,shader);
	if(param != nullptr)
	{
		cgGLSetParameter3f(param, vec.r, vec.g, vec.b);
		checkForCgError("Setting parameter");
		return true;
	}
	return false;
}
bool  ShaderManager::setCgParam(glm::vec4 vec, const char * name, Shader shader)
{
	CGparameter param = getParamFromShader(name,shader);
	if(param != nullptr)
	{
		cgGLSetParameter4f(param, vec.r, vec.g, vec.b,vec.a);
		checkForCgError("Setting parameter");
		return true;
	}
	return false;
}
bool  ShaderManager::setCgParam(glm::mat4x4 mat, const char * name, Shader shader)
{
	CGparameter param = getParamFromShader(name,shader);
	if(param != nullptr)
	{
		cgGLSetMatrixParameterfc(param, &mat[0][0]);
		checkForCgError("Setting parameter");
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
	else if(currentStage == StateManager::TRANSPARENCY_STAGE && shader == VERTEX)
	{
		param = cgGetNamedParameter(cgTransparencyStageVP, name);
		checkForCgError(name);
	}
	else if(currentStage == StateManager::TRANSPARENCY_STAGE && shader == FRAGMENT)
	{
		param = cgGetNamedParameter(cgTransparencyStageFP, name);
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
StateManager & ShaderManager::getStateManager()
{
	return stateManager;
}
