#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <GL/freeglut.h>
#include "Hipotrocoide.h"
//#include <GL/glut.h>
#include "Coche.h"
#include "Camara.h"

#include <iostream>
using namespace std;

// Freeglut parameters
// Flag telling us to keep processing events
// bool continue_in_main_loop= true; //(**)

// Viewport size
int WIDTH = 500, HEIGHT = 500;

// Viewing frustum parameters
GLdouble xRight = 10, xLeft = -xRight, yTop = 10, yBot = -yTop, N = 1, F = 1000;

// Camera parameters
GLdouble eyeX = 100.0, eyeY = 100.0, eyeZ = 100.0;
GLdouble lookX = 0.0, lookY = 0.0, lookZ = 0.0;
GLdouble upX = 0, upY = 1, upZ = 0;

// Scene variables
GLfloat angX, angY, angZ;


//HIPOTROCOIDE
Hipotrocoide h(16, 250, 7, 4, 2);

bool line_ = false;

//COCHE
float g;
GLfloat gCoche = 0.0f;
Coche newCoche(1, 1, 1, 1, 1, 1, gCoche);
float rotRuedas;


//CAMARA
GLfloat gRoll = 0;
PV3D* eye = new PV3D(eyeX, eyeY, eyeZ, 1);
PV3D* look = new PV3D(lookX, lookY, lookZ, 0);
PV3D* up = new PV3D(upX, upY, upZ, 0);
Camara* cam = new Camara(eye, look, up);

GLUquadricObj * q;

void buildSceneObjects() {
	angX = 0.0f;
	angY = 0.0f;
	angZ = 0.0f;

}

void initGL() {
	glClearColor(0.6f, 0.7f, 0.8f, 1.0);

	glEnable(GL_COLOR_MATERIAL);
	glMaterialf(GL_FRONT, GL_SHININESS, 0.9f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH); // Shading by default

	buildSceneObjects();

	// Light0
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat d[] = { 0.7f,0.5f,0.5f,1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, d);
	GLfloat a[] = { 0.3f,0.3f,0.3f,1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, a);
	GLfloat s[] = { 1.0f,1.0f,1.0f,1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, s);
	GLfloat p[] = { 25.0f, 25.0f, 25.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, p);

	//prueba
	/*GLfloat d[] = { 0, 1, 0, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, d);
	GLfloat a[] = { 0, 0, 0, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, a);
	GLfloat s[] = { 1.0f,1.0f,1.0f,1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, s);
	GLfloat p[] = { 0, 10, 10, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, p);
	GLfloat lmb[] = { 0, 0, 0, 1 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmb);*/




	// Camera set up
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, lookX, lookY, lookZ, upX, upY, upZ);

	// Frustum set up
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(xLeft, xRight, yBot, yTop, N, F);

	// Viewport set up
	glViewport(0, 0, WIDTH, HEIGHT);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	//focos luz
	GLfloat p[] = { 0, 10, 10, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, p);

	glPushMatrix();

	// Rotating the scene
	glRotatef(angX, 1.0f, 0.0f, 0.0f);
	glRotatef(angY, 0.0f, 1.0f, 0.0f);
	glRotatef(angZ, 0.0f, 0.0f, 1.0f);

	glLineWidth(1.5f);
	// Drawing axes
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0, 0, 0);
	glVertex3f(20, 0, 0);

	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 20, 0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 20);
	glEnd();

	// Drawing the scene	 		 
	glColor3f(1.0, 1.0, 1.0);
	
	//HIPOTROCOIDE
	h.dibuja();

	//COCHE
	g = atan2(h.C2(gCoche)->getX(), h.C2(gCoche)->getZ());
	g = (g * 360) / (2 * 3.1415926);
	glTranslated(h.C(gCoche)->getX(), h.C(gCoche)->getY(), h.C(gCoche)->getZ());
	glRotated(-90, 0, 1, 0);
	glRotated(g, 0, 1, 0);
	
	q = gluNewQuadric();
	
	//PARA PRUEBAS DE LUZ
	/*
	glPushMatrix();
	glTranslated(7, 0, 0);
	glutSolidSphere(2, 30, 30);
	glPopMatrix();
	*/

	newCoche.dibujaCoche(rotRuedas, q);

	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}


void resize(int newWidth, int newHeight) {
	WIDTH = newWidth;
	HEIGHT = newHeight;
	GLdouble RatioViewPort = (float)WIDTH / (float)HEIGHT;
	glViewport(0, 0, WIDTH, HEIGHT);

	GLdouble SVAWidth = xRight - xLeft;
	GLdouble SVAHeight = yTop - yBot;
	GLdouble SVARatio = SVAWidth / SVAHeight;
	if (SVARatio >= RatioViewPort) {
		GLdouble newHeight = SVAWidth / RatioViewPort;
		GLdouble yMiddle = (yBot + yTop) / 2.0;
		yTop = yMiddle + newHeight / 2.0;
		yBot = yMiddle - newHeight / 2.0;
	}
	else {
		GLdouble newWidth = SVAHeight*RatioViewPort;
		GLdouble xMiddle = (xLeft + xRight) / 2.0;
		xRight = xMiddle + newWidth / 2.0;
		xLeft = xMiddle - newWidth / 2.0;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(xLeft, xRight, yBot, yTop, N, F);
}

void key(unsigned char key, int x, int y) {
	bool need_redisplay = true;
	switch (key) {
	case 27:  /* Escape key */
			  //continue_in_main_loop = false; // (**)
			  //Freeglut's sentence for stopping glut's main loop (*)
		glutLeaveMainLoop();
		break;
	case 'a': angX = angX + 5; break;
	case 'z': angX = angX - 5; break;
	case 's': angY = angY + 5; break;
	case 'x': angY = angY - 5; break;
	case 'd': angZ = angZ + 5; break;
	case 'c': angZ = angZ - 5; break;
	case 'l':
		h.line = !h.line;
		break;
	default:
		need_redisplay = false;
		break;
	case 'e':
		break;
	case 'f':
		gCoche += 0.1;
		rotRuedas -= 10;
		break;
	case 'v':
		gCoche -= 0.1;
		rotRuedas += 10;
		break;
	case 'q':
		cam->roll();
		break;
	case '1':
		cam->giraX();
	case'h': 
		glEnable(GL_LIGHT0);
	//	lightSwitch(GL_TRUE); 
		break;
	case 'n': 
		glDisable(GL_LIGHT0);
	//	lightSwitch(GL_FALSE); 
		break;
	case 'g':
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
		break;

	case 'b':
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
		break;
	}

	if (need_redisplay)
		glutPostRedisplay();
}

int main(int argc, char *argv[]) {
	cout << "Starting console..." << endl;

	int my_window; // my window's identifier

				   // Initialization
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(0, 0);
	//glutInitWindowPosition (140, 140);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInit(&argc, argv);

	// Window construction
	my_window = glutCreateWindow("Freeglut 3D-project");

	// Callback registration
	glutReshapeFunc(resize);
	glutKeyboardFunc(key);
	glutDisplayFunc(display);

	// OpenGL basic setting
	initGL();

	// Freeglut's main loop can be stopped executing (**)
	// while (continue_in_main_loop) glutMainLoopEvent();

	// Classic glut's main loop can be stopped after X-closing the window,
	// using the following freeglut's setting (*)
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

	// Classic glut's main loop can be stopped in freeglut using (*)
	glutMainLoop();

	// We would never reach this point using classic glut
	system("PAUSE");

	return 0;
}