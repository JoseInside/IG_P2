#include "Coche.h"
#include "Hipotrocoide.h"


Coche::~Coche()
{
	gluDeleteQuadric(q);
}

void Coche::dibujaCoche(GLfloat girRueda, GLUquadricObj * q) {

	glColor3f(0, 1, 0);
	glutSolidCube(1);

	//RUEDAS
	glPushMatrix();
	glTranslated(0.4, -0.4, 0.2);
	glRotatef(-girRueda, 0, 0, 1);
	glColor3d(1, 1, 0);
	gluCylinder(q, 0.4f, 0.4f, 0.5f, 15, 15);
	glTranslatef(0, 0, 0.5);
	glPopMatrix();
	
	glPushMatrix();
	glTranslated(-0.4, -0.4, 0.2);
	glRotatef(-girRueda, 0, 0, 1);
	glColor3d(1, 1, 0);
	gluCylinder(q, 0.4f, 0.4f, 0.5f, 15, 15);
	glTranslatef(0, 0, 0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -0.5);
	glTranslated(0.4, -0.4, -0.2);
	glRotatef(-girRueda, 0, 0, 1);
	glColor3d(1, 1, 0);
	gluCylinder(q, 0.4f, 0.4f, 0.5f, 15, 15);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0, 0, -0.5);
	glTranslated(-0.4, -0.4, -0.2);
	glRotatef(-girRueda, 0, 0, 1);
	glColor3d(1, 1, 0);
	gluCylinder(q, 0.4f, 0.4f, 0.5f, 15, 15);
	glPopMatrix();

	//FAROS
	/*glPushMatrix();
	glColor3d(1, 1, 1);
	glRotatef(90, 0, 1, 0);
	glTranslatef(-1, 0, 0.8);
	gluCylinder(q, 0.2f, 0.2f, 0.5f, 15, 3);
	glPopMatrix();
	*/
	GLfloat pos1[] = { 0, 0, 0, 1.0f };
	GLfloat dir[] = { 1, 0, 0 };


//	glLightfv(GL_LIGHT1, GL_POSITION, pos1);
//	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dir);


	glTranslated(0, 0, -1);

	glPushMatrix();
	glColor3d(1, 1, 1);
	glTranslatef(1, 0, 0.5);
	glRotatef(90, 0, 1, 0);
	gluCylinder(q, 0.2f, 0.2f, 0.5f, 15, 3);
	glPopMatrix();

	//glLightfv(GL_LIGHT2, GL_POSITION, pos1);
//	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, dir);

	glPopMatrix();

}