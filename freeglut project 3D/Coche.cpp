#include "Coche.h"



Coche::Coche()
{
	q = gluNewQuadric();
}


Coche::~Coche()
{
	gluDeleteQuadric(q);
}
