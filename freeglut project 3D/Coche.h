#pragma once
#include <GL/freeglut.h>
class Coche
{
public:
	Coche();
	~Coche();
	
	GLUquadricObj* q;
	
	
	int glutSolidCube(GLdouble tam);
	int gluCylinder(GLUquadricObj* q, baseRadius, topRadius, height, slices, stacks);

	GLfloat girRueda;
};

