#include "StateHandler.h"

DEBUG_STATE StateHandler::getDebugState()
{
	return debugState;
}
void StateHandler::toggleDebugState(DEBUG_STATE state)
{
	debugState = state;
}