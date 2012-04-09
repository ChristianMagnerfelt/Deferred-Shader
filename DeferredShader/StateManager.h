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
			TRANSPARENCY_STAGE,
		};
		StateManager() : currentDebugState(NO_DEBUG), 
			currentRenderingStage(GEOMETRY_STAGE), renderTransperency(false){}

		debugState getDebugState() const;
		renderingStage getRenderingStage() const;
		bool getRenderTransperency() const;

		void setDebugState(debugState state);
		void setRenderingStage(renderingStage stage);
		void setRenderTransperency(const bool value);
	private:
		debugState currentDebugState;
		renderingStage currentRenderingStage;
		bool renderTransperency;
};