#include "RenderApp.h"

void RenderApp::setupViewvolume() {
	Vector eye(0.0, 1.0, 2.0),
		   view(0.0, 0.0, 0.0),
		   up(0.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, float(1024)/768, 0.1, 20.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//eye.x = 2.5; eye.y = 1.8; eye.z = 2.0;
	gluLookAt(eye.x, eye.y, eye.z, view.x, view.y, view.z, up.x, up.y, up.z);
}

void RenderApp::setupLights() {
	float light_ambient[]  = { 0.3f, 0.3f, 0.3f, 1.0f };
	float light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
	float light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float light_position[] = { -1.5f, 2.0f, 2.0f, 0.0f }; 

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);

	glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position); 

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void RenderApp::setupMaterial() {
	const float mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
	const float mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
	const float mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
	const float high_shininess[] = { 100.0f }; 

	glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess); 
}

void drawStuff() {
	GLfloat vertices[] = {
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		1.0, 1.0, 0.0,
		1.0, 0.0, 0.0,
		0.0, 0.0, 1.0,
		0.0, 1.0, 1.0,
		1.0, 1.0, 1.0,
		1.0, 0.0, 1.0
	};

	GLubyte face[] = {
		4,7,6,5, // front
		0,3,2,1, // back
		3,2,6,7, // right
		1,0,4,5, // left
		5,6,2,1, // top
		3,7,4,0  // bottom
	};

	GLfloat normal[6][3] = {
		0.0, 0.0, 1.0,
		0.0, 0.0, -1.0,
		1.0, 0.0, 0.0,
		-1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, -1.0, 0.0
	};

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 3*sizeof(GLfloat), vertices);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for(int i=0; i<6; ++i) {
		glNormal3fv(normal[i]);
		glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, &face[4*i]);
	}

	glPushMatrix();
        glTranslatef(0, 0, 3.0);
        glutSolidSphere(0.1,50,50);
    glPopMatrix(); 						

	/*
	struct point front[4] = { {0,0,1}, {0,1,1}, {1,1,1}, {1,0,1} };
	struct point back[4]  = { {1,0,0}, {1,1,0}, {0,1,0}, {0,0,0} };
	struct point left[4]  = { {0,0,0}, {0,1,0}, {0,1,1}, {0,0,1} };
	struct point right[4] = { {1,0,1}, {1,1,1}, {1,1,0}, {1,0,0} };
	struct point top[4]   = { {0,1,1}, {0,1,0}, {1,1,0}, {1,1,1} };
	struct point bottom[4]= { {0,0,0}, {0,0,1}, {1,0,1}, {1,0,0} };

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1, 0.1, 0.1, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glPolygonMode(GL_FRONT, GL_LINE);
	//glPolygonMode(GL_BACK, GL_LINE);
	//glColor3f(1.0, 1.0, 0.0);
	//glLineWidth(2.0);
	

	glBegin(GL_QUADS);
	
	int i;
	glColor3f(1.0, 0.0, 0.0);
	
	glNormal3f(0, 0, 1);
	for(i=0; i<4; i++) glVertex3f(front[i].x, front[i].y, front[i].z);
	
	glNormal3f(0, 0, -1);
	for(i=0; i<4; i++) glVertex3f(back[i].x, back[i].y, back[i].z);
	glColor3f(0.0, 1.0, 0.0);

	glNormal3f(-1, 0, 0);
	for(i=0; i<4; i++) glVertex3f(left[i].x, left[i].y, left[i].z);
	
	glNormal3f(1, 0, 0);
	for(i=0; i<4; i++) glVertex3f(right[i].x, right[i].y, right[i].z);
	glColor3f(0.0, 0.0, 1.0);
	
	glNormal3f(0, 1, 0);
	for(i=0; i<4; i++) glVertex3f(top[i].x, top[i].y, top[i].z);

	glNormal3f(0, -1, 0);
	for(i=0; i<4; i++) glVertex3f(bottom[i].x, bottom[i].y, bottom[i].z);
	
	glEnd();
	/*
	glutSolidSphere(0.1, 50, 50);
	glPushMatrix();
        glTranslatef(0, 0, 3.0);
        glutSolidSphere(0.1,50,50);
    glPopMatrix(); 
	*/
	glutSwapBuffers();
}

void RenderApp::drawStuff2() {
	//std::cout<< "draw()" << std::endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);	

	Vector bottom[4]= { Vector(1, -0.2, 1), Vector(1, -0.2, -1), 
		                Vector(-1, -0.2, -1), Vector(-1, -0.2, 1) };
	
	// draw a sphere at origin
    glPushMatrix();
    glTranslated(0.0, 0.0, 0.0);
    glutSolidSphere(origin.getRadius(), 50, 50);
    glPopMatrix();

	// the sphere to be grabbed
	glPushMatrix();
	Vector temp = grabBall.getCenter();
	glTranslated(temp.x, temp.y, temp.z);
	glutSolidSphere(grabBall.getRadius(), 50, 50);
	glPopMatrix();
 
	// draw the hands
	if(controller.isConnected()) {
		FingerList fingers = controller.frame().fingers();
		InteractionBox ibox = controller.frame().interactionBox();

		for(int i=0; i<fingers.count(); ++i) {
			Finger finger = fingers[i];
			Vector joints[5];
			joints[0] = leapToWorld(finger.tipPosition(), ibox);
			glPushMatrix();
			glTranslatef(joints[0].x, joints[0].y, joints[0].z);
			glutSolidSphere(0.015, 30, 30);
			glPopMatrix();

			for(int b=3; b>=0; b--) {
				Bone::Type boneType = static_cast<Bone::Type>(b);
				joints[4-b] = leapToWorld(finger.bone(boneType).prevJoint(), ibox);
				glPushMatrix();
				glTranslatef(joints[4-b].x, joints[4-b].y, joints[4-b].z);
				glutSolidSphere(0.015, 30, 30);
				glPopMatrix();

				glLineWidth(5.0);
				glBegin(GL_LINES);
				glColor3f(1.0, 0.0, 0.0);
				glVertex3f(joints[4-b].x, joints[4-b].y, joints[4-b].z);
				glVertex3f(joints[4-b-1].x, joints[4-b-1].y, joints[4-b-1].z);
				glEnd();
			}
		}
	}
	
	glBegin(GL_QUADS);
	for(int i=0; i<4; ++i)
		glVertex3f(bottom[i].x, bottom[i].y, bottom[i].z);
	glEnd();
	
    glutSwapBuffers();
}

void RenderApp::update() {
	if(controller.isConnected()) {
		int numHand = controller.frame().hands().count();
		if (numHand != 0) {
			InteractionBox ibox = controller.frame().interactionBox();
			HandList hands = controller.frame().hands();			
					
			int index = 0;
			float dist = grabBall.getCenter().distanceTo(leapToWorld(hands[0].palmPosition(), ibox));
			for(int i=1; i<numHand; ++i) {
				Vector pos = leapToWorld(hands[i].palmPosition(), ibox);
				float d = grabBall.getCenter().distanceTo(pos);
				index = (d < dist) ? i : index;
				dist = (d < dist) ? d : dist;
			}

			if(grabBall.isGrabbed()) {
				if(hands[index].grabStrength() > 0.8) {
					Vector pos = leapToWorld(hands[index].palmPosition(), ibox);
					grabBall.setCenter(pos + hands[index].palmNormal() * grabBall.getRadius());
				}
				else
					grabBall.setGrab(false);
			}
			else {
				if(dist < grabBall.getRadius() && hands[index].grabStrength() > 0.8) {
					grabBall.setGrab(true);
					Vector pos = leapToWorld(hands[index].palmPosition(), ibox);
					grabBall.setCenter(pos + hands[index].palmNormal() * grabBall.getRadius());
				}
			}


			std::cout << "distance: " << dist << ", grabe: " << hands[index].grabStrength() << std::endl;
			
			
			
			glutPostRedisplay();



		}
	}
}

void RenderApp::handleKey(unsigned char key, int x, int y){
  switch(key){    
    case 'q': case 'Q': case 27: // esc - quit
		exit(0);
	case 'r': case 'R': 
		init();
		glutPostRedisplay();
    default:
		return;
  }
}

void RenderApp::init() {
	origin.setCenter(Vector(0.0, 0.0, 0.0));
	origin.setRadius(0.03);
	grabBall.setCenter(Vector(0.5, 0.5, 0.5));
	grabBall.setRadius(0.1);

}

Vector RenderApp::leapToWorld(const Vector &leapPoint, const InteractionBox &iBox)
{
    //leapPoint.z *= -1.0; //right-hand to left-hand rule
    Vector normalized = iBox.normalizePoint(leapPoint, false);
    normalized += Vector(-0.5, 0, -0.5); //recenter origin
    return (normalized * 1.0); //scale
}