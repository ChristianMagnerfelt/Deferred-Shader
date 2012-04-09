#include "Scene.h"

#include "Model.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

Scene::Scene()
{
}
Scene::~Scene()
{
	for(ModelVector::iterator it = modelVector.begin(); it != modelVector.end(); ++it)
	{
		delete (*it);
	}
	for(LightVector::iterator it = lightVector.begin(); it != lightVector.end(); ++it)
	{
		delete (*it);
	}
}
void Scene::loadContent(ContentManager & contentManager)
{
	/**Model * solidBox = new Model();
	contentManager.loadModel().loadAssimpScene(std::string("content/box.obj"),*solidBox);

	Entity box1 (glm::vec3(10.0,0.0,-50.0),glm::vec3(1.0,1.0,1.0),glm::vec4(0.0,0.0,0.0,0.0));
	Entity box2 (glm::vec3(10.0,0.0,-40.0),glm::vec3(1.0,1.0,1.0),glm::vec4(0.0,0.0,0.0,0.0));
	Entity box3 (glm::vec3(0.0,0.0,-40.0),glm::vec3(1.0,1.0,1.0),glm::vec4(0.0,0.0,0.0,0.0));
	Entity box4 (glm::vec3(0.0,0.0,-50.0),glm::vec3(1.0,1.0,1.0),glm::vec4(0.0,0.0,0.0,0.0));
	solidBox->addEntity(box1);
	solidBox->addEntity(box2);
	solidBox->addEntity(box3);
	solidBox->addEntity(box4);
	
	GLuint difTex = contentManager.loadTexture().loadRAWRGBTexture("content/fieldstone-c.raw",512,512);
	GLuint normTex = contentManager.loadTexture().loadRAWRGBTexture("content/fieldstone-n.raw",512,512);
	solidBox->setDiffuseTexID(difTex);
	solidBox->setNormalTexID(normTex);

	solidBox->setCurrentMaterial(Material::materialId("lambert5SG"));
	Material mat = solidBox->getMaterial("lambert5SG");
	mat.setOpacity(1.0);
	mat.setDiffuseColor(glm::vec3(0.5,0.5,0.5));
	mat.setSpecularColor(glm::vec3(0.5,0.5,0.5));
	solidBox->updateMaterial(mat);

	modelVector.push_back(solidBox);**/

	Model * transparentBox = new Model();
	contentManager.loadModel().loadAssimpScene(std::string("content/box.obj"),*transparentBox);

	for(unsigned int i = 0; i < 20; i += 10)
	{
		for(unsigned int j = 0; j < 20; j += 10)
		{
			Entity box (glm::vec3(i,0.0,j),glm::vec3(1.0,1.0,1.0),glm::vec4(0.0,0.0,0.0,0.0));
			transparentBox->addEntity(box);
		}
	}
	/**Entity box5 (glm::vec3(10.0,0.0,-30.0),glm::vec3(1.0,1.0,1.0),glm::vec4(0.0,0.0,0.0,0.0));
	Entity box6 (glm::vec3(10.0,0.0,-20.0),glm::vec3(1.0,1.0,1.0),glm::vec4(0.0,0.0,0.0,0.0));
	Entity box7 (glm::vec3(0.0,0.0,-20.0),glm::vec3(1.0,1.0,1.0),glm::vec4(0.0,0.0,0.0,0.0));
	Entity box8 (glm::vec3(0.0,0.0,-30.0),glm::vec3(1.0,1.0,1.0),glm::vec4(0.0,0.0,0.0,0.0));
	transparentBox->addEntity(box5);
	transparentBox->addEntity(box6);
	transparentBox->addEntity(box7);
	transparentBox->addEntity(box8);**/
	
	GLuint difTexO = contentManager.loadTexture().loadRAWRGBTexture("content/fieldstone-c.raw",512,512);
	GLuint normTexO = contentManager.loadTexture().loadRAWRGBTexture("content/fieldstone-n.raw",512,512);
	transparentBox->setDiffuseTexID(difTexO);
	transparentBox->setNormalTexID(normTexO);

	transparentBox->setCurrentMaterial(Material::materialId("lambert5SG"));
	Material matO = transparentBox->getMaterial("lambert5SG");
	matO.setOpacity(0.5);
	matO.setDiffuseColor(glm::vec3(0.5,0.5,0.5));
	matO.setAmbientColor(glm::vec3(0.1,0.1,0.1));
	matO.setSpecularColor(glm::vec3(0.5,0.5,0.5));
	transparentBox->updateMaterial(matO);

	modelVector.push_back(transparentBox);

	// Lights
	Light * pointLight1 = new Light(glm::vec3(-10,0,0),glm::vec3(1.0,1.0,1.0),30.0);
	Light * pointLight2 = new Light(glm::vec3(-10,0,0),glm::vec3(1.0,1.0,1.0),15.0);
	Light * pointLight3 = new Light(glm::vec3(0,0,-10),glm::vec3(1.0,1.0,1.0),15.0);

	lightVector.push_back(pointLight1);
	lightVector.push_back(pointLight2);
	lightVector.push_back(pointLight3);
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
			// Only render transperent objects in the transperent stage
			if((*it)->isTransperent() && shaderManager.getStateManager().getRenderingStage() != StateManager::TRANSPARENCY_STAGE) continue;
			else if(!(*it)->isTransperent() && shaderManager.getStateManager().getRenderingStage() == StateManager::TRANSPARENCY_STAGE) continue;

			for(Model::EntityVector::iterator entIt = (*it)->getAllEntities().begin(); entIt != (*it)->getAllEntities().end(); ++entIt)
			{
				glPushMatrix();
				glTranslatef(entIt->position.x,entIt->position.y,entIt->position.z);
				glRotatef(entIt->rotation.w,entIt->rotation.x,entIt->rotation.y,entIt->rotation.z);
				glScalef(entIt->scale.x,entIt->scale.y,entIt->scale.z);
				shaderManager.updateModelviewPerspectiveMatrix();
				if(shaderManager.getStateManager().getRenderingStage() == StateManager::TRANSPARENCY_STAGE)
				{
					glm::mat4x4 tlMat = glm::translate(glm::mat4x4(1.0),entIt->position);
					//glm::mat4x4 rotMat = glm::rotate(tlMat, entIt->rotation.w,glm::vec3(entIt->rotation.x,entIt->rotation.y,entIt->rotation.z));
					//glm::mat4x4 scMat = glm::scale(rotMat, entIt->scale);
					shaderManager.setCgParam(tlMat,"modelMatrix",VERTEX);
				}
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
void Scene::sortEntities(Camera & camera)
{
	for(ModelVector::iterator it = modelVector.begin(); it != modelVector.end(); ++it)
	{
		std::sort((*it)->getAllEntities().begin(), (*it)->getAllEntities().end(), [&camera](Entity & a, Entity & b) -> bool
		{
			if((camera.getEyePoint() - a.position).length() < (camera.getEyePoint() - b.position).length())
			{
				return true;
			}
			else
			{
				return false;
			}
		});
	}
}

