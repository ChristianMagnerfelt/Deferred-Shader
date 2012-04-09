
#include "TransparencyRenderer.h"
#include "Util.h"

void TransparencyRenderer::draw(Scene & scene, Camera & camera)
{
	stateManager.setRenderingStage(StateManager::TRANSPARENCY_STAGE);
	
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);			// Bind Framebuffer
	checkGLErrors("Binding framebuffer");							
	checkFramebufferStatus();								// Check that framebuffer config OK
	
	shaderManager.bindStageShader();						// Bind Transparency stage shaders

	glDisable(GL_BLEND);										// Enable blending
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);		// Set blend func for optimized Transparency rendering
	glEnable(GL_CULL_FACE);								// Disable face culling
	glEnable(GL_DEPTH_TEST);								// Disable Z-Buffer
	glDisable(GL_TEXTURE_2D);								// Disable textures

	//camera.setGLModelView();
	//camera.setGLProjection();
	//camera.calculatePlanes();								// Will later be used for culling

	scene.sortEntities(camera);								// Sort entities by depth

	drawLights(scene,camera);

	glDisable(GL_BLEND);
}

void TransparencyRenderer::drawLights(Scene & scene, Camera & camera)
{
	glm::vec4 eyePosition = glm::vec4(camera.getEyePoint(),1.0) * camera.getModelViewMatrix();
	shaderManager.setCgParam(eyePosition, "eyePosition", VERTEX);
	for (unsigned int i = 0; i < scene.getLightVector().size(); ++i)
	{
		glm::vec4 lightPosition = glm::vec4(scene.getLightVector()[i]->getPosition(),1.0) * camera.getModelViewMatrix();		
		shaderManager.setCgParam(lightPosition,"lightPosition",VERTEX);
		shaderManager.setCgParam(scene.getLightVector()[i]->getColor(),"lightColor",FRAGMENT);
		shaderManager.setCgParam(scene.getLightVector()[i]->getRadius(),"radius",FRAGMENT);

		scene.draw(shaderManager);								// Draw transperent objects
	}
}