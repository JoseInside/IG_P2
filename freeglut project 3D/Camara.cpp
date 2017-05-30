#include "Camara.h"



Camara::Camara(PV3D* eye, PV3D* look, PV3D* up)
{
	eye_ = eye;  //situacion
	look_ = look;  //direccion (donde mira)
	up_ = up;  //orientacion

	
	//volumen de vista
	left = 10;
	right = 10;
	top = 10;
	bottom = 10;
	near_ = 1;
	far_ = 1000;
	fovy = 10;
	aspect = 10;


	//matriz de vista
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye_->getX(), eye_->getY(), eye_->getZ(), look_->getX(), look_->getY(), look_->getZ(), up_->getX(), up_->getY(), up_->getZ());

	//matriz de proyeccion
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(left, right, bottom, top, near_, far_);

	asignarValores();
	rMatriz();

	d = new PV3D(0, eye_->getY() - look_->getY(), eye_->getZ() - look_->getZ(), 0);
}


Camara::~Camara()
{
}
void Camara::rMatriz() {

	//u,v,n,eye_

	Vista[0] = u->getX();
	Vista[1] = u->getY();
	Vista[2] = u->getZ();
	Vista[3] = 0;

	Vista[4] = v->getX();
	Vista[5] = v->getY();
	Vista[6] = v->getZ();
	Vista[7] = 0;

	Vista[8] = n_->getX();
	Vista[9] = n_->getY();
	Vista[10] = n_->getZ();
	Vista[11] = 0;

	Vista[12] = eye_->getX();
	Vista[13] = eye_->getY();
	Vista[14] = eye_->getZ();
	Vista[15] = 1;
}
void Camara::rMatrizInv() {

	//u,v,n,eye_

	Vista2[0] = u->getX();
	Vista2[1] = v->getX();
	Vista2[2] = n_->getX();
	Vista2[3] = 0;

	Vista2[4] = u->getY();
	Vista2[5] = v->getY();
	Vista2[6] = n_->getY();
	Vista2[7] = 0;

	Vista2[8] = u->getZ();
	Vista2[9] = v->getZ();
	Vista2[10] = n_->getZ();
	Vista2[11] = 0;

	Vista2[12] = -eye_->productoEscalar(u);
	Vista2[13] = -eye_->productoEscalar(v);
	Vista2[14] = -eye_->productoEscalar(n_);
	Vista2[15] = 1;
}
void Camara::asignarValores() {

	//n_
	PV3D* i = new PV3D(eye_->getX() - look_->getX(), eye_->getY() - look_->getY(), eye_->getZ() - look_->getZ(), 0);

	i->normaliza(eye_->getX() - look_->getX(), eye_->getY() - look_->getY(), eye_->getZ() - look_->getZ());

	n_ = i;

	//u
	PV3D* j = up_->productoVectorial(n_);
	j->normaliza(up_->getX(), up_->getY(), up_->getZ());  //posible error


	u = j;

	//v
	v = n_->productoVectorial(u);
}
void Camara::roll() {

	glMatrixMode(GL_MODELVIEW);

	//u global
	PV3D* i = new PV3D(u->getX()* cos(n) + v->getX() * sin(n), u->getY()* cos(n) + v->getY() * sin(n), u->getZ()* cos(n) + v->getZ() * sin(n), 0);


	//v  global
	PV3D* j = new PV3D(-u->getX()* sin(n) + v->getX() * cos(n), -u->getY()* sin(n) + v->getY() * cos(n), -u->getZ()* sin(n) + v->getZ() * cos(n), 0);

	u = i;
	v = j;

	rMatriz();
	rMatrizInv();
	glLoadMatrixf(Vista2);

}

void Camara::giraX() {

	glMatrixMode(GL_MODELVIEW);

	x += 0.05;

	r = sqrt(d->getY() * d->getY() + d->getZ() * d->getZ());
	eye_ = new PV3D(eye_->getX(), r * sin(n), r * cos(n), 1);

	asignarValores();

	rMatriz();
	glLoadIdentity();
	gluLookAt(eye_->getX(), eye_->getY(), eye_->getZ(), look_->getX(), look_->getY(), look_->getZ(), up_->getX(), up_->getY(), up_->getZ());
}
