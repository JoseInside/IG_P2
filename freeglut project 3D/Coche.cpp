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
	
	//FAROS + LUZ	

	
	GLfloat amb[] = { 1, 1, 0, 1.0 };
	GLfloat dif[] = { 1, 1, 1, 1 };
	GLfloat spc[] = { 1, 1, 1, 1 };

	//FARO dcha

	glLightfv(GL_LIGHT1, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, dif);
	glLightfv(GL_LIGHT1, GL_SPECULAR, spc);

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 50);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 4);

	GLfloat pos1[] = { 0, 0, 0, 1.0f };
	GLfloat dir[] = { 1, 0, 0 };
	glLightfv(GL_LIGHT1, GL_POSITION, pos1);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dir);


	glPushMatrix();
	glColor3d(1, 1, 1);
	glRotatef(90, 0, 1, 0);
	glTranslatef(-0.5, 0, 0.5);
	gluCylinder(q, 0.2f, 0.2f, 0.5f, 15, 3);
	glPopMatrix();

	//FARO izda
	glTranslated(0, 0, -1);

	glLightfv(GL_LIGHT2, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, dif);
	glLightfv(GL_LIGHT2, GL_SPECULAR, spc);

	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 50);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 4);

	glLightfv(GL_LIGHT2, GL_POSITION, pos1);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, dir);

	glPushMatrix();
	glColor3d(1, 1, 1);
	glTranslatef(0.45, 0, 0.5);
	glRotatef(90, 0, 1, 0);
	gluCylinder(q, 0.2f, 0.2f, 0.5f, 15, 3);
	glPopMatrix();

	glLightfv(GL_LIGHT2, GL_POSITION, pos1);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, dir);

	glPopMatrix();

}