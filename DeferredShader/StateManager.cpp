#include "StateManager.h"

StateManager::debugState StateManager::getDebugState() const
{
	return currentDebugState;
}
StateManager::renderingStage StateManager::getRenderingStage() const
{
	return currentRenderingStage;
}
void StateManager::setDebugState(StateManager::debugState state)
{
	currentDebugState = state;
}
void StateManager::setRenderingStage(StateManager::renderingStage stage)
{
	currentRenderingStage = stage;
}