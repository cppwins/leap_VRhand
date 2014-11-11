#include <gl\glew.h>
#include <gl\glut.h>
#include "Sphere.h"
#include "Leap.h"
using namespace Leap;

class RenderApp {
public:
	static RenderApp *getInstance() {
		if(!instance)
			instance = new RenderApp;
		return instance;
	}

	void setupViewvolume();
	void setupLights();
	void setupMaterial();
	
	void drawStuff2();
	void update();
	void handleKey(unsigned char, int, int);

	static void displayFunc() {
		RenderApp::getInstance()->drawStuff2();
	}

	static void idleFunc() {
		RenderApp::getInstance()->update();
	}

	static void keyFunc(unsigned char key, int x, int y) {
		RenderApp::getInstance()->handleKey(key, x, y);
	}

	void init();

private:
	RenderApp() { init(); }
	RenderApp(const RenderApp&) {}
	RenderApp& operator=(const RenderApp&) {}
	Vector leapToWorld(const Vector &, const InteractionBox &);

	static RenderApp *instance;
	Controller controller;
	Sphere origin, grabBall;
};