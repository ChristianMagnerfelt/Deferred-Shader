/**
@author: Christian Magnerfelt
@version: 2012.01.17
**/

#pragma once

#include "Util.h"



class StateManager
{
	public:
		enum debugState
		{
			NO_DEBUG,
			DIFFUSE_BUFFER,
			NORMAL_BUFFER,
			SPECULAR_BUFFER,
			DEPTH_BUFFER
		};

		// TODO: Post-processing Stage
		enum renderingStage
		{
			GEOMETRY_STAGE,
			LIGHTING_STAGE,
			DEBUG_STAGE,
		};
		StateManager() : currentDebugState(NO_DEBUG), 
			currentRenderingStage(GEOMETRY_STAGE){}

		debugState getDebugState() const;
		renderingStage getRenderingStage() const;

		void setDebugState(debugState state);
		void setRenderingStage(renderingStage stage);
	private:
		debugState currentDebugState;
		renderingStage currentRenderingStage;
};