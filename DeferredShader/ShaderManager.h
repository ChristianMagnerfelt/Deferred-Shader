/**
@author: Christian Magnerfelt
@version: 2012.01.17
**/

#pragma once 

#include "Util.h"

enum TextureOptions {
	MODEL_TEXTURE,
	MODEL_NORMAL_MAP,
	GB_DEBUG
};
enum MaterialOptions {
	SPECULAR
};
enum Stage
{
	GEOMETRY_STAGE,
	LIGTHING_STAGE,
	DEBUG_STAGE,
};

class ShaderManager 
{
	public:
		ShaderManager() : programName("DS ShaderManager") {}
		~ShaderManager();
		void initShader();

		void bindGeometryStageShader();
		void unbindGeometryStageShader();
		void bindDebugShader();
		void bindLightingStageShader();
		void unbindLightingStageShader();

		void updateModelviewMatrix();
		void updateModelviewPerspectiveMatrix(Stage stage);

		void bindCGParameter(CGparameter & parameter, const char * name);
		void bindCGTexture(GLuint & texID, TextureOptions);
		void bindCGMaterial(Float4 value, MaterialOptions options);

		void checkForCgError(const char * situation);
	private:
		CGcontext cgContext;
		CGprofile cgVertexProfile, cgFragmentProfile;
		CGprogram cgGeometryStageVP, cgGeometryStageFP, cgDebugVP, cgDebugFP;
		const char * programName;
};