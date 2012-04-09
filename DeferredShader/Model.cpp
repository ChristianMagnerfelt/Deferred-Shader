#include "Model.h"
#include "ShaderManager.h"

#include <iostream>
#include <algorithm>
#include <exception>

Model::Model() : hasDiffuseTex(false), hasNormalTex(false), 
	hasVertexBuf(false) 
{
	materials.insert(Material());
	currentMaterial = std::string("default");
}
Model::~Model()
{
	if(hasDiffuseTexture())
	{
		glDeleteTextures(1,&diffuseTexID);
	}
	if(hasNormalTexture())
	{
		glDeleteTextures(1,&normalTexID);
	}
	if(hasVertexBuffer())
	{
		glDeleteBuffersARB(1,&vertexBufferID);
	}
}
void Model::draw(ShaderManager & shader)
{
	shader.bindCGTexture(getDiffuseTexID(),COLOR_TEXTURE);
	shader.bindCGTexture(getNormalTexID(),NORMAL_TEXTURE);
	MaterialSet::const_iterator it = std::find(materials.begin(), materials.end(), currentMaterial);
	if(it != materials.end())
	{
		shader.setCgParam(it->getDiffuseColor(),"diffuse",FRAGMENT);
		shader.setCgParam(it->getSpecularColor(),"specular",FRAGMENT);
		shader.setCgParam(it->getShinyness(),"shinyness",FRAGMENT);
		shader.setCgParam(it->getAmbientColor(),"ambient",FRAGMENT);
		if(shader.getStateManager().getRenderingStage() == StateManager::TRANSPARENCY_STAGE)
		{
			shader.setCgParam(it->getOpacity(),"opacity",FRAGMENT);
		}
	}

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vertexBufferID);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3,GL_FLOAT,0,0);
	glNormalPointer(GL_FLOAT,0,(void*)(getNumVertices() * 3 * sizeof(float)));
	
	glClientActiveTexture(GL_TEXTURE0);
	glTexCoordPointer(3,GL_FLOAT,0,(void*)(getNumVertices() * 3 * sizeof(float) * 2));

	glClientActiveTexture(GL_TEXTURE1);
	glTexCoordPointer(3,GL_FLOAT,0,(void*)(getNumVertices() * 3 * sizeof(float) * 3));

	glDrawArrays(GL_TRIANGLES,0,getNumVertices());
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
}
bool Model::hasDiffuseTexture() const
{
	return hasDiffuseTex;
}
bool Model::hasNormalTexture() const
{
	return hasNormalTex;
}
bool Model::hasVertexBuffer() const
{
	return hasVertexBuf;
}
unsigned int Model::getDiffuseTexID() const
{
	return diffuseTexID;
}
unsigned int Model::getNormalTexID() const
{
	return normalTexID;
}
unsigned int Model::getVertexBufferID() const
{
	return vertexBufferID;
}
unsigned int Model::getNumVertices() const
{
	return numVertices;
}
void Model::setDiffuseTexID(unsigned int & id)
{
	if(hasDiffuseTexture());
	else hasDiffuseTex = true;
	diffuseTexID = id;
}
void Model::setNormalTexID(unsigned int & id)
{
	if(hasNormalTexture());
	else hasNormalTex = true;
	normalTexID = id;
}
void Model::setVertexBufferID(unsigned int & id)
{
	if(hasVertexBuffer()) glDeleteBuffersARB(1,&vertexBufferID);
	else hasVertexBuf = true;
	vertexBufferID = id;
}
void Model::addMaterial(Material mat)
{
	materials.insert(mat);
}
void Model::removeMaterial(Material::materialId id)
{
	MaterialSet::iterator it = std::find(materials.begin(), materials.end(), id);
	if(it != materials.end())
	{	
		materials.erase(it);
	}
}
Material Model::getMaterial(Material::materialId id)
{
	MaterialSet::iterator it = std::find(materials.begin(), materials.end(), id);
	if(it == materials.end())
	{
		throw std::exception("No such element");
	}
	return *it;
}
void Model::setCurrentMaterial(Material::materialId id)
{
	if(std::find(materials.begin(), materials.end(), id) != materials.end())
	{
		currentMaterial = id;
		std::cout << "Material set to " << id << std::endl;
	}
	else
	{
		std::cout << "Material " << id << " does not exist" << std::endl;
	}
}
void Model::setNumVertices(unsigned int & id)
{
	numVertices = id;
}
void Model::addEntity(Entity & entity)
{
	entityVector.push_back(entity);
}
Model::EntityVector & Model::getAllEntities()
{
	return entityVector;
}
const Material::materialId & Model::getCurrentMaterial() const
{
	return currentMaterial;
}
bool Model::isTransperent() const
{
	MaterialSet::const_iterator it = std::find(materials.begin(), materials.end(), currentMaterial); 
	if(it == materials.end())
	{
		std::cerr << "No Material set" << std::endl;
		throw std::exception("Material Missing");
	}
	if(it->getOpacity() < 1.0 )
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Model::updateMaterial(Material & mat)
{
	removeMaterial(mat.getID());
	addMaterial(mat);
}