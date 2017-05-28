#include "Coche.h"
#include "Hipotrocoide.h"


Coche::~Coche()
{
	gluDeleteQuadric(q);
}

void Coche::dibujaCoche(GLfloat girRueda) {

	glutSolidCube(1);
	
}