#include "PV3D.h"

PV3D::PV3D(GLfloat x, GLdouble y, GLfloat z, int pv)
{// si lo pones a this no hace falta usar referencia en los metodos de esta clase ya que es instancia a ellos mismos (creo)
	this->pv = pv;
	this->x = x;
	this->y = y;
	this->z = z;
}


PV3D::~PV3D()
{
}

PV3D* PV3D::clona(){

	return new PV3D(x, y, z, pv);
}


PV3D* PV3D::normaliza(GLfloat x, GLfloat y, GLfloat z){

	/*PV3D* p = new PV3D(x, y, z, 0);

	GLfloat modulo = sqrtf(fabs(pow(p->x,2) + pow(p->y, 2) + pow(p->z, 2)));
	//p->productoEscalar(p);

	p->x = p->x / modulo;
	p->y = p->y / modulo;
	p->z = p->z / modulo;
	return p;*/
	GLfloat modulo2 = productoEscalar(this);
	PV3D* p = new PV3D(x, y, z, 0);
	if (modulo2>0) {
		p->x = x / sqrt(modulo2);
		p->y = y / sqrt(modulo2);
		p->z = z / sqrt(modulo2);
	}
	return p;
}


GLfloat PV3D::productoEscalar(PV3D* v){
	//sqrt((int)x * (int)x + y ^ 2 + z ^ 2) * sqrt((int)v->getX() ^ 2 + v->getY() ^ 2 + v->getZ() ^ 2);

	return x*v->getX() + y*v->getY() + z*v->getZ();
}
PV3D* PV3D::productoVectorial(PV3D* v){
	
	PV3D * pVectorial = new PV3D(0, 0, 0, 0);
	pVectorial->x = y*v->getZ() - z*v->getY();
	pVectorial->y = z*v->getX() - x*v->getZ();
	pVectorial->z = x*v->getY() - y*v->getX();

	return pVectorial;
}