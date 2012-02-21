#include "Scene.h"

#include "Model.h"
#include "RTGModel.h"

#include <vector>

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
	// Load Box
	Model * box = new RTGModel(contentManager.loadModel().loadRTG("content/Box.rtg", true));
	Entity boxEnt1 (Float3(0.0,0.0,0.0),Float3(1.0,1.0,1.0),Float4(0.0,0.0,0.0,0.0));
	box->addEntity(boxEnt1);	
	GLuint boxTex = contentManager.loadTexture().loadRAWRGBTexture("content/Box.raw",256,256);
	box->setDiffuseTexID(boxTex);
	modelVector.push_back(box);

	Model * bigSphere = new RTGModel(contentManager.loadModel().loadRTG("content/BigSphere.rtg", true));
	Entity bigSphereEnt1 (Float3(-5.0,-4.0,-3.0),Float3(1.0,1.0,1.0),Float4(0.0,0.0,0.0,0.0));
	bigSphere->addEntity(bigSphereEnt1);
	GLuint bigSphereTex = contentManager.loadTexture().loadRAWRGBTexture("content/BigSphere.raw",256,256);
	bigSphere->setDiffuseTexID(bigSphereTex);
	modelVector.push_back(bigSphere);

	Model * cylinder = new RTGModel(contentManager.loadModel().loadRTG("content/Cylinder.rtg", true));
	Entity cylinderEnt1 (Float3(5.0,1.0,-4.0),Float3(1.0,1.5,1.0),Float4(0.0,0.0,0.0,0.0));
	cylinder->addEntity(cylinderEnt1);
	GLuint cylinderTex = contentManager.loadTexture().loadRAWRGBTexture("content/Cylinder.raw",256,256);
	cylinder->setDiffuseTexID(cylinderTex);
	modelVector.push_back(cylinder);

	Model * smallS1 = new RTGModel(contentManager.loadModel().loadRTG("content/SmallSphere1.rtg", true));		
	Entity smallS1Ent1 (Float3(1.0,-5.0,-1.0),Float3(1.0,1.0,1.0),Float4(0.0,0.0,0.0,0.0));					
	smallS1->addEntity(smallS1Ent1);														
	GLuint smallSTex = contentManager.loadTexture().loadRAWRGBTexture("content/SmallSphere.raw",256,256);
	smallS1->setDiffuseTexID(smallSTex);
	modelVector.push_back(smallS1);																		

	Model * smallS2 = new RTGModel(contentManager.loadModel().loadRTG("content/SmallSphere2.rtg", true));
	Entity smallS2Ent1 (Float3(-2,-5.0,3.0),Float3(1.0,1.0,1.0),Float4(0.0,0.0,0.0,0.0));						
	smallS2->addEntity(smallS2Ent1);																			
	smallS2->setDiffuseTexID(smallSTex);
	modelVector.push_back(smallS2);	

	Model * brood = new RTGModel(contentManager.loadModel().loadRTG("content/brood.rtg", true));
	Entity broodEnt (Float3(4.0,-6.0,1.0),Float3(0.5,0.5,0.5),Float4(0.0,0.0,0.0,0.0));
	brood->addEntity(broodEnt);														
	GLuint broodTex = contentManager.loadTexture().loadRAWRGBTexture("content/brood.raw",512,512);
	brood->setDiffuseTexID(broodTex);
	modelVector.push_back(brood);	
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
			for(EntityVector::iterator entIt = (*it)->getAllEntities().begin(); entIt != (*it)->getAllEntities().end(); ++entIt)
			{
				glPushMatrix();
				glTranslatef(entIt->position.x,entIt->position.y,entIt->position.z);
				glRotatef(entIt->rotation.w,entIt->rotation.x,entIt->rotation.y,entIt->rotation.z);
				glScalef(entIt->scale.x,entIt->scale.y,entIt->scale.z);
				shaderManager.updateModelviewPerspectiveMatrix(GEOMETRY_STAGE);
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