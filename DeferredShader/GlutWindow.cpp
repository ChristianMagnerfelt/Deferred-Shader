#include "GlutWindow.h"

inline void frwDisplay(void){gGlutWindow->display();}
inline void frwReshape(GLsizei w, GLsizei h){gGlutWindow->reshape(w,h);}
inline void frwKeyboard(unsigned char c, int x, int y){gGlutWindow->keyboard(c,x,y);}
inline void frwIdle(void){gGlutWindow->idle();}
inline void frwMouseClick(int b, int s, int x, int y){gGlutWindow->mouseClick(b,s,x,y);}
inline void frwMouseMove(int x, int y){gGlutWindow->mouseMove(x,y);}

GlutWindow::GlutWindow()
	: camera(SCREEN_WIDTH, SCREEN_HEIGHT), 
	shaderManager(stateManager), 
	deferredShader(stateManager, shaderManager), 
	transperencyRenderer(shaderManager, stateManager)
{
	gGlutWindow = this;
}
GlutWindow::~GlutWindow()
{
	gGlutWindow = 0;
}
void GlutWindow::printGLInfo()
{
	std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
}
void GlutWindow::init(int & argc, char * argv [])
{
	glutInit(&argc, argv);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
	glutCreateWindow(programName);
	printGLInfo();

	GLenum glewErr = glewInit();
	if (GLEW_OK != glewErr)
	{
	/* Problem: glewInit failed, something is seriously wrong. */
		std::cout << glewGetErrorString(glewErr) << std::endl;
	}

	glutDisplayFunc(frwDisplay);
	//glutReshapeFunc(GL_FALSE); // TODO: reshape when I'm not lazy
	glutKeyboardFunc(frwKeyboard);
	glutIdleFunc(frwIdle);
	glutMouseFunc(frwMouseClick);
	glutMotionFunc(frwMouseMove);

	deferredShader.init(camera);
	scene.loadContent(contentManager);

	camera.setCameraPerspective(30.0,1.5,5.0,1000.0);
	camera.setCameraPosition(
		glm::vec3(-26.0,10.0,-20.0),
		glm::vec3(0.0,4.0,0.0),
		glm::vec3(0.0,1.0,0.0));
	camera.setCameraSpeed(0.01);
	glutWarpPointer(SCREEN_WIDTH/2, SCREEN_HEIGHT/2); // Reset mouse
	//glutSetCursor(GLUT_CURSOR_NONE); 
}
void GlutWindow::display()
{
	deferredShader.draw(scene,camera);
	if(stateManager.getRenderTransperency())
	{
		transperencyRenderer.draw(scene,camera);
	}
	drawFPS();
	glutSwapBuffers();
}
void GlutWindow::reshape(GLsizei width, GLsizei height)
{
   if (height == 0) height = 1;											// prevent divide by 0

   // Set the viewport (display area) to cover entire application window
   glViewport(0, 0, width, height);

   // Select the aspect ratio of the clipping area to match the viewport
   glMatrixMode(GL_PROJECTION);												// Select the Projection matrix
   glLoadIdentity();														// Reset the Projection matrix
   gluPerspective(45.0, (float)width / (float)height, 0.1, 100.0);			// fovy, aspect ratio, zNear, zFar

   // Reset the Model-View matrix
   glMatrixMode(GL_MODELVIEW);												// Select the Model-View matrix
   glLoadIdentity();														// Reset the Model-View matrix
}
void GlutWindow::keyboard(unsigned char & key, int & x , int & y)
{
	switch(key)
	{
		case (49) :
			stateManager.setDebugState(StateManager::NO_DEBUG);
			break;
		case (50) :
			stateManager.setDebugState(StateManager::DIFFUSE_BUFFER);
			break;
		case (51) :
			stateManager.setDebugState(StateManager::NORMAL_BUFFER);
			break;
		case (52) :
			stateManager.setDebugState(StateManager::SPECULAR_BUFFER);
			break;
		case (53) :
			stateManager.setDebugState(StateManager::DEPTH_BUFFER);
			break;
		case (54) :
			if(stateManager.getRenderTransperency()) 
			{
				stateManager.setRenderTransperency(false);
			}
			else
			{
				stateManager.setRenderTransperency(true);
			}
			break;
		case (87 ) :											//W
		case (119) :											//w
			camera.moveCamera(camera.getCameraSpeed());
			break;
		case (65) :												//A
		case (97) :												//a
			camera.rotateView(-camera.getCameraSpeed());
			break;
		case (83) :												//S
		case (115) :											//s
			camera.moveCamera(-camera.getCameraSpeed());
			break;
		case (68) :												//D
		case (100) :											//d
			camera.rotateView(camera.getCameraSpeed());
			break;
		default :
			break;
	}
}
void GlutWindow::idle()
{
	camera.mouseMove();										// Update mouse movement
	calculateFPS();
	glutPostRedisplay();
}
void GlutWindow::run()
{
	glutMainLoop();
}
void GlutWindow::mouseClick(int button, int state, int x, int y) {
	if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		camera.setFocus(true);
	}else if(button == GLUT_LEFT_BUTTON)
	{
		camera.setFocus(false);
	}
}

void GlutWindow::mouseMove(int x, int y) {
	camera.setMouseX(x);
	camera.setMouseY(y);
}
void GlutWindow::drawFPS()
{
    //  Load the identity matrix so that FPS string being drawn
    //  won't get animates
	glLoadIdentity ();

	//  Print the FPS to the window
	std::cout << "FPS:" << fps << std::endl;
}
void GlutWindow::calculateFPS()
{
    //  Increase frame count
    frameCount++;

    //  Get the number of milliseconds since glutInit called 
    //  (or first call to glutGet(GLUT ELAPSED TIME)).
    currentTime = glutGet(GLUT_ELAPSED_TIME);

    //  Calculate time passed
    int timeInterval = currentTime - previousTime;

    if(timeInterval > 1000)
    {
        //  calculate the number of frames per second
        fps = frameCount / (timeInterval / 1000.0f);

        //  Set time
        previousTime = currentTime;

        //  Reset frame count
        frameCount = 0;
    }
}