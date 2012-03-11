#include "GlutWindow.h"

int main(int argc, char * argv [])
{
	static GlutWindow window;
	window.init(argc,argv);
	window.run();
}