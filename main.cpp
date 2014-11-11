#include <string>
#include "RenderApp.h"

RenderApp *RenderApp::instance = NULL;

int main(int argc, char* argv[]){
	RenderApp *app = RenderApp::getInstance();
	
	// start up the glut utilities
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1024, 768);
	glutCreateWindow("Grab that ball!");

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.8, 0.8, 0.8, 0.0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK); 

	app->setupViewvolume();
	app->setupLights();
	//app->setupMaterial();

	glutDisplayFunc(RenderApp::displayFunc);
	glutIdleFunc(RenderApp::idleFunc);
	//glutReshapeFunc(resize);
	glutKeyboardFunc(RenderApp::keyFunc);

	glutMainLoop();
	return 0;
}