#include "GlutWindow.h"

inline void frwDisplay(void){gGlutWindow->display();}
inline void frwReshape(GLsizei w, GLsizei h){gGlutWindow->reshape(w,h);}
inline void frwKeyboard(unsigned char c, int x, int y){gGlutWindow->keyboard(c,x,y);}
inline void frwIdle(void){gGlutWindow->idle();}
inline void frwMouseClick(int b, int s, int x, int y){gGlutWindow->mouseClick(b,s,x,y);}
inline void frwMouseMove(int x, int y){gGlutWindow->mouseMove(x,y);}

GlutWindow::GlutWindow()
{
	gGlutWindow = this;
}
GlutWindow::~GlutWindow()
{
	gGlutWindow = 0;
}
void GlutWindow::printGLInfo()
{
	cout << "OpenGL Version : " << glGetString(GL_VERSION) << endl;
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
		cout << glewGetErrorString(glewErr) << endl;
	}

	glutDisplayFunc(frwDisplay);
	//glutReshapeFunc(GL_FALSE);
	glutKeyboardFunc(frwKeyboard);
	glutIdleFunc(frwIdle);
	glutMouseFunc(frwMouseClick);
	glutMotionFunc(frwMouseMove);

	deferredShader.init(SCREEN_WIDTH,SCREEN_HEIGHT);
	scene.loadContent(contentManager);

	camera.setCameraPerspective(30.0,1.5,3.0,100.0);
	camera.setCameraPosition(
		Float3(6.0,-2.0,32.0),
		Float3(0.0,1.0,0.0),
		Float3(0.0,1.0,0.0));
	camera.setCameraSpeed(0.01);
	glutWarpPointer(SCREEN_WIDTH/2, SCREEN_HEIGHT/2); // Reset mouse
	glutSetCursor(GLUT_CURSOR_NONE); 
}
void GlutWindow::display()
{
	deferredShader.draw(scene,camera,stateHandler);
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
			stateHandler.toggleDebugState(DIFFUSE_BUFFER);
			break;
		case (50) :
			stateHandler.toggleDebugState(NORMAL_BUFFER);
			break;
		case (51) :
			stateHandler.toggleDebugState(SPECULAR_BUFFER);
			break;
		case (52) :
			stateHandler.toggleDebugState(DEPTH_BUFFER);
			break;
		case (87 ) :											//W
		case (119) :											//w
			camera.moveCamera(camera.speed);
			break;
		case (65) :												//A
		case (97) :												//a
			camera.rotateView(-camera.speed);
			break;
		case (83) :												//S
		case (115) :											//s
			camera.moveCamera(-camera.speed);
			break;
		case (68) :												//D
		case (100) :											//d
			camera.rotateView(camera.speed);
			break;
		default :
			break;
	}
}
void GlutWindow::idle()
{
	glutPostRedisplay();
}
void GlutWindow::run()
{
	glutMainLoop();
}
void GlutWindow::mouseClick(int button, int state, int x, int y) {
	//
}

void GlutWindow::mouseMove(int x, int y) {
	//
	camera.mouseX = x;
	camera.mouseY = y;
}

