/**
@author: Christian Magnerfelt
@version: 2012.01.17
**/

#pragma once

#include "Util.h"

enum DEBUG_STATE
{
	NO_DEBUG,
	DIFFUSE_BUFFER,
	NORMAL_BUFFER,
	SPECULAR_BUFFER,
	DEPTH_BUFFER
};

class StateHandler
{
	public:
		StateHandler() : debugState(NO_DEBUG){}
		DEBUG_STATE getDebugState();
		void toggleDebugState(DEBUG_STATE);
	private:
		DEBUG_STATE debugState;
};