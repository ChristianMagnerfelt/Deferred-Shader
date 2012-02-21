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

}
void ShaderManager::updateModelviewPerspectiveMatrix(Stage stage)
{
	CGparameter modelviewProjMatrix;
	if(stage == GEOMETRY_STAGE)
	{
		modelviewProjMatrix = cgGetNamedParameter(cgGeometryStageVP, "modelViewProj");
	}
	else if(stage == DEBUG_STAGE)
	{
		modelviewProjMatrix = cgGetNamedParameter(cgDebugVP, "modelViewProj");
	}
	cgGLSetStateMatrixParameter(modelviewProjMatrix, CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);
	checkForCgError("Setting Modelview Projection Matrix");
}
void ShaderManager::bindCGParameter(CGparameter & parameter, const char * name)
{

}
void ShaderManager::bindCGTexture(GLuint & texID, TextureOptions options)
{
	CGparameter texture_param;
	if(options == MODEL_TEXTURE)
	{
		texture_param = cgGetNamedParameter(cgGeometryStageFP, "colortex");
	}
	else if(options == MODEL_NORMAL_MAP)
	{
		texture_param = cgGetNamedParameter(cgGeometryStageFP, "normaltex");
	}
	else if(options == GB_DEBUG)
	{
		texture_param = cgGetNamedParameter(cgDebugFP, "gbTex");
	}
	else
	{
		return;
	}
	checkForCgError("Getting Texture Parameter");

	cgGLSetTextureParameter(texture_param, texID);
	cgGLEnableTextureParameter(texture_param);
	checkForCgError("Setting 2D Texture ");
}
void ShaderManager::bindCGMaterial(Float4 mat, MaterialOptions options)
{
	CGparameter param;
	param = cgGetNamedParameter(cgGeometryStageFP, "specular");
	cgGLSetParameter4f(param, mat.x, mat.y, mat.z, mat.w);
	checkForCgError("Setting Material");
}
void ShaderManager::checkForCgError(const char * situation)
{
	CGerror error;
	const char *string = cgGetLastErrorString(&error);

	if (error != CG_NO_ERROR) 
	{
		cerr << programName << " : " << situation << " : " << string << endl;
		if (error == CG_COMPILER_ERROR) 
		{
			cerr << cgGetLastListing(cgContext) << endl;
		}
		system("pause");
		exit(1);
  }
}