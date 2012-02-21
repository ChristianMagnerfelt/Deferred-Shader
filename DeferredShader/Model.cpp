#include "Model.h"		

unsigned int Model::getDiffuseTexID()
{
	return diffuseTexID;
}
unsigned int Model::getNormalMapID()
{
	return normalMapID;
}
void Model::setDiffuseTexID(unsigned int & texID)
{
	diffuseTexID = texID;
}
void Model::setNormalMapID(unsigned int & texID)
{
	normalMapID = texID;
}
void Model::addEntity(Entity & entity)
{
	entityVector.push_back(entity);
}
EntityVector & Model::getAllEntities()
{
	return entityVector;
}