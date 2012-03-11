#include "Scene.h"

#include "Model.h"
#include "RTGModel.h"
#include <glm/glm.hpp>

#include <vector>
#include <string>
#include <iostream>

Scene::Scene()
{
}
Scene::~Scene()
{
	for(ModelVector::iterator it = modelVector.begin(); it != modelVector.end(); ++it)
	{
		delete (*it);
	}
}
void Scene::loadContent(ContentManager & contentManager)
{
	Model * box = new Model();
	contentManager.loadModel().loadAssimpScene(std::string("content/box.obj"),*box);

	Entity box1 (glm::vec3(10.0,0.0,0.0),glm::vec3(1.0,1.0,1.0),glm::vec4(0.0,0.0,0.0,0.0));
	Entity box2 (glm::vec3(10.0,0.0,10.0),glm::vec3(1.0,1.0,1.0),glm::vec4(0.0,0.0,0.0,0.0));
	Entity box3 (glm::vec3(0.0,0.0,10.0),glm::vec3(1.0,1.0,1.0),glm::vec4(0.0,0.0,0.0,0.0));
	Entity box4 (glm::vec3(0.0,0.0,0.0),glm::vec3(1.0,1.0,1.0),glm::vec4(0.0,0.0,0.0,0.0));
	box->addEntity(box1);
	box->addEntity(box2);
	box->addEntity(box3);
	box->addEntity(box4);
	
	GLuint difTex = contentManager.loadTexture().loadRAWRGBTexture("content/fieldstone-c.raw",512,512);
	GLuint normTex = contentManager.loadTexture().loadRAWRGBTexture("content/fieldstone-n.raw",512,512);
	box->setDiffuseTexID(difTex);
	box->setNormalTexID(normTex);

	box->setCurrentMaterial(Material::materialId("lambert5SG"));

	modelVector.push_back(box);
}
/**
*	Draw scene
**/
void Scene::draw(ShaderManager & shaderManager)
{
	for(ModelVector::iterator it = modelVector.begin(); it != modelVector.end(); ++it)
	{
		if((*it) != 0)
		{
			for(Model::EntityVector::iterator entIt = (*it)->getAllEntities().begin(); entIt != (*it)->getAllEntities().end(); ++entIt)
			{
				
				glPushMatrix();
				glTranslatef(entIt->position.x,entIt->position.y,entIt->position.z);
				glRotatef(entIt->rotation.w,entIt->rotation.x,entIt->rotation.y,entIt->rotation.z);
				glScalef(entIt->scale.x,entIt->scale.y,entIt->scale.z);
				shaderManager.updateModelviewPerspectiveMatrix();
				shaderManager.updateModelviewMatrix();
				(*it)->draw(shaderManager);
				glPopMatrix();
			}
		}
	}
}
LightVector & Scene::getLightVector()
{
	return lightVector;
}