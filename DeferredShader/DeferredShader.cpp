#include "DeferredShader.h"

#include "StateManager.h"

DeferredShader::DeferredShader(StateManager & stateM, ShaderManager & shaderM) : stateManager(stateM), shaderManager(shaderM)
{}
DeferredShader::~DeferredShader()
{
	cleanUp();
}
void DeferredShader::init(Camera & camera)	
{
	GLsizei screenWidth = camera.getScreenWidth();
	GLsizei screenHeight = camera.getScreenHeight();
	std::cout << "Buffer dimensions : " << screenWidth << " x " << screenHeight << std::endl;

	// Init G-Buffer
	checkFramebufferEXTSupport();	

	// Create texture to store diffuse color data
	glGenTextures(1, &gbDiffuse);
	glBindTexture(GL_TEXTURE_2D, gbDiffuse);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, screenWidth, screenHeight, 0,
             GL_RGB, GL_UNSIGNED_BYTE, 0);
	std::cout << "GbDiffuse Tex : " << gbDiffuse << std::endl;

	// Create texture to store normal data
	glGenTextures(1, &gbNormal);
	glBindTexture(GL_TEXTURE_2D, gbNormal);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, screenWidth, screenHeight, 0,
             GL_RGB, GL_UNSIGNED_BYTE, 0);
	std::cout << "GbNormal Tex : " << gbNormal << std::endl;

	// Create texture to store specular data
	glGenTextures(1, &gbSpecular);
	glBindTexture(GL_TEXTURE_2D, gbSpecular);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, screenWidth, screenHeight, 0,		// Specular data includes specular r,g,b and shininess component
             GL_RGBA, GL_UNSIGNED_BYTE, 0);
	std::cout << "GbSpecular Tex : " << gbSpecular << std::endl;
	
	// Create depth texture
	glGenTextures(1, &gbDepth);
	glBindTexture(GL_TEXTURE_2D, gbDepth);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, screenWidth, screenHeight, 0,		// 24 bit depth texture format
             GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	std::cout << "GbDepth Tex : " << gbDepth << std::endl;
	glBindTexture(GL_TEXTURE_2D, 0);

	// Create FBO
	glGenFramebuffersEXT(1, &fbo);
	checkGLErrors("Generate FBO");
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
	checkGLErrors("Bind FBO");
	std::cout << "FBO ID: " << fbo << std::endl;

	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT,
                          GL_TEXTURE_2D, gbDepth, 0);
	checkGLErrors("Attach depth renderbuffer to FBO");

	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,
                          GL_TEXTURE_2D, gbDiffuse, 0);
	checkGLErrors("Attach diffuse texture to FBO");

	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT1_EXT,
                          GL_TEXTURE_2D, gbNormal, 0);
	checkGLErrors("Attach normal texture to FBO");

	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT2_EXT,
                          GL_TEXTURE_2D, gbSpecular, 0);
	checkGLErrors("Attach specular texture to FBO");

	// Enable drawing for all color buffer attachments
	GLenum drawbuffers[] = {   GL_COLOR_ATTACHMENT0_EXT, 
		GL_COLOR_ATTACHMENT1_EXT,
		GL_COLOR_ATTACHMENT2_EXT}; 
	glDrawBuffers(3, drawbuffers); 
	
	checkFramebufferStatus();

	// Load all shaders
	shaderManager.initShader();
}
void DeferredShader::cleanUp()
{
	glDeleteFramebuffersEXT(1, &fbo);
}
void DeferredShader::draw(Scene & scene, Camera & camera)
{
	geometryStage(scene,camera);
	if(stateManager.getDebugState() != StateManager::NO_DEBUG)
	{
		debugStage(camera);
	}
	else 
	{
		lightingStage(scene,camera);
	}
}
void DeferredShader::bindGBuffer()
{
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);			// Bind FBO
	checkGLErrors("Binding FBO");							
	checkFramebufferStatus();								// Check that framebuffer config OK
}
void DeferredShader::unbindGBuffer()
{
	
}
void DeferredShader::bindPBuffer()
{
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);			// Bind Framebuffer
	checkGLErrors("Binding FBO");							
	checkFramebufferStatus();								// Check that framebuffer config OK

	
}
void DeferredShader::unbindPBuffer()
{
	
}
void DeferredShader::geometryStage(Scene & scene, Camera & camera)
{
	stateManager.setRenderingStage(StateManager::GEOMETRY_STAGE);

	bindGBuffer();											// Bind G-Buffer for rendering

	shaderManager.bindStageShader();						// Bind geometry stage shaders

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear color & depth bit
	glCullFace(GL_BACK);									// Set culling method			
	glEnable(GL_CULL_FACE);									// Enable face culling
	glDisable(GL_BLEND);									// Disable stencil buffer	
	glDepthFunc(GL_LEQUAL);									// Set Z-Test method
	glEnable(GL_DEPTH_TEST);								// Enable Z-Buffer
	glDisable(GL_TEXTURE_2D);								// Disable textures

	
	camera.setGLProjection();								// Set up Projection Matrix
	camera.setGLModelView();								// Set up Modelview Matrix
	//camera.calculatePlanes();

	scene.draw(shaderManager);								// Draw scene

	unbindGBuffer();										// Unbind G-buffer
}
void DeferredShader::drawLights()
{

}
void DeferredShader::debugStage(Camera & camera)
{
	stateManager.setRenderingStage(StateManager::DEBUG_STAGE);

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);			// Debug
	checkGLErrors("Bind framebuffer");

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_CULL_FACE);								// Disable Cull Face
	glDisable(GL_DEPTH_TEST);								// Disable Z-Buffer
	
	shaderManager.bindStageShader();

	if(stateManager.getDebugState() == StateManager::DIFFUSE_BUFFER)
	{
		shaderManager.bindCGTexture(gbDiffuse,GB_DEBUG);
	}
	else if(stateManager.getDebugState() == StateManager::NORMAL_BUFFER)
	{
		shaderManager.bindCGTexture(gbNormal,GB_DEBUG);
	}
	else if(stateManager.getDebugState() == StateManager::SPECULAR_BUFFER)
	{
		shaderManager.bindCGTexture(gbSpecular,GB_DEBUG);
	}
	else if(stateManager.getDebugState() == StateManager::DEPTH_BUFFER)
	{
		shaderManager.bindCGTexture(gbDepth,GB_DEBUG);
	}
	drawRec(camera);
}
void DeferredShader::lightingStage(Scene & scene, Camera & camera)
{
	stateManager.setRenderingStage(StateManager::LIGHTING_STAGE);
	bindPBuffer();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_CULL_FACE);								// Disable Cull Face
	glDisable(GL_DEPTH_TEST);								// Disable Z-Buffer

	shaderManager.bindStageShader();

	shaderManager.setCgParam(gbDepth,"depthMap",FRAGMENT);
	shaderManager.setCgParam(gbDiffuse,"diffuseMap",FRAGMENT);
	shaderManager.setCgParam(gbSpecular,"specularMap",FRAGMENT);
	shaderManager.setCgParam(gbNormal,"normalMap",FRAGMENT);

	shaderManager.setCgParam(camera.getZNear(),"near",FRAGMENT);
	shaderManager.setCgParam(camera.getZFar(),"far",FRAGMENT);
	drawLighting(scene,camera);
	unbindPBuffer();
}
void DeferredShader::drawAmbient()
{
	
}
void DeferredShader::drawLighting(Scene & scene, Camera & camera)
{
	glEnable(GL_BLEND);
	for (unsigned int i = 0; i < scene.getLightVector().size(); ++i)
	{
		for(unsigned int j = 0; j < 5; ++j)
		{

		}

		glm::vec4 lightPos(scene.getLightVector()[i]->getPosition(),1.0);
		glm::vec4 viewPos(camera.getEyePoint(),1.0);

		lightPos = (lightPos * camera.getModelViewMatrix()) * camera.getProjectionMatrix();
		viewPos = (viewPos * camera.getModelViewMatrix()) * camera.getProjectionMatrix();

		shaderManager.setCgParam(lightPos,"lightPos",FRAGMENT);
		shaderManager.setCgParam(viewPos,"viewPos",FRAGMENT);
		shaderManager.setCgParam(scene.getLightVector()[i]->getColor(),"lightColor",FRAGMENT);
		shaderManager.setCgParam(scene.getLightVector()[i]->getRadius(),"radius",FRAGMENT);

		drawRec(camera);
	}
	glDisable(GL_BLEND);
}
void DeferredShader::drawRec(Camera & camera)
{
	/**glMatrixMode (GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity ();
	
	glMatrixMode (GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity ();

	shaderManager.updateModelviewPerspectiveMatrix();

	glMatrixMode (GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode (GL_PROJECTION);
	glPopMatrix();
	**/

	// Draw full screen rectangle
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex2f(-1, -1);
		glTexCoord2f(1, 0);
		glVertex2f(1, -1);
		glTexCoord2f(1, 1);
		glVertex2f(1, 1);
		glTexCoord2f(0, 1);
		glVertex2f(-1, 1);
	glEnd();
}

int DeferredShader::lightScissorTest(const glm::vec3 & position, float radius, int sx, int sy, Camera & camera)
{
	int rect[4]={ 0,0,sx,sy };						// Set scissor rectangle equal to whole viewplane
	float d;

	float r = radius;									// Get radius of light source
	float r2 = r*r;

	glm::vec3 l = position;
	glm::vec3 l2 = glm::sqrt(l);
	float e1=1.2f;
	float e2=1.2f*camera.getAspectRatio();

	d=r2*l2.x - (l2.x+l2.z)*(r2-l2.z);
	if (d>=0)
	{
		d=sqrtf(d);

		float nx1=(r*l.x + d)/(l2.x+l2.z);
		float nx2=(r*l.x - d)/(l2.x+l2.z);

		float nz1=(r-nx1*l.x)/l.z;
		float nz2=(r-nx2*l.x)/l.z;

		float e=1.25f;
		float a=camera.getAspectRatio();

		float pz1=(l2.x+l2.z-r2)/(l.z-(nz1/nx1)*l.x);
		float pz2=(l2.x+l2.z-r2)/(l.z-(nz2/nx2)*l.x);

		if (pz1<0)
		{
			float fx=nz1*e1/nx1;
			int ix=(int)((fx+1.0f)*sx*0.5f);

			float px=-pz1*nz1/nx1;
			if (px<l.x)
			{
				rect[0]=std::max(rect[0],ix);
			}
			else
			{
				rect[2]=std::min(rect[2],ix);
			}
			if (pz2<0)
			{
				float fx=nz2*e1/nx2;
				int ix=(int)((fx+1.0f)*sx*0.5f);

				float px=-pz2*nz2/nx2;
				if (px<l.x)
					rect[0]=std::max(rect[0],ix);
				else
					rect[2]=std::min(rect[2],ix);
			}
		}

		d=r2*l2.y - (l2.y+l2.z)*(r2-l2.z);
		if (d>=0)
		{
			d=sqrtf(d);

			float ny1=(r*l.y + d)/(l2.y+l2.z);
			float ny2=(r*l.y - d)/(l2.y+l2.z);

			float nz1=(r-ny1*l.y)/l.z;
			float nz2=(r-ny2*l.y)/l.z;

			float pz1=(l2.y+l2.z-r2)/(l.z-(nz1/ny1)*l.y);
			float pz2=(l2.y+l2.z-r2)/(l.z-(nz2/ny2)*l.y);
			
			if (pz1<0)
			{
				float fy=nz1*e2/ny1;
				int iy=(int)((fy+1.0f)*sy*0.5f);

				float py=-pz1*nz1/ny1;
				if (py<l.y)
				{
					rect[1]=std::max(rect[1],iy);
				}
				else
				{
					rect[3]=std::min(rect[3],iy);
				}

				if (pz2<0)
				{
					float fy=nz2*e2/ny2;
					int iy=(int)((fy+1.0f)*sy*0.5f);

					float py=-pz2*nz2/ny2;
					if (py<l.y)
					{
						rect[1]=std::max(rect[1],iy);
					}
					else
					{
						rect[3]=std::min(rect[3],iy);
					}
				}
			}
		
		int n=(rect[2]-rect[0])*(rect[3]-rect[1]);
		if (n<=0)
		{
			return 0;
		}
		if (n==sx*sy)
		{
			glDisable(GL_SCISSOR_TEST);
			return sx*sy;
		}
		glScissor(rect[0],rect[1],rect[2]-rect[0],rect[3]-rect[1]);
		glEnable(GL_SCISSOR_TEST);
		
		return n;
		}
	}
}