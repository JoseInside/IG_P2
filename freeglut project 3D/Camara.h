#pragma once
#include "Malla.h"
#include "GL\freeglut.h"

class Camara
{
public:
	Camara(PV3D* eye, PV3D* look, PV3D* up);
	~Camara();


	void roll();
	void giraX();



	PV3D* eye_;
	PV3D* look_;
	PV3D* up_;
	PV3D* u;
	PV3D* v;
	PV3D* n_;

	PV3D* d;

	GLdouble left;
	GLdouble right;
	GLdouble top;
	GLdouble bottom;
	GLdouble near_;
	GLdouble far_;
	GLdouble fovy;
	GLdouble aspect;

	GLfloat Vista[16];
	GLfloat Vista2[16];

	GLdouble r;
	GLdouble rot = 0.05; //angulo rotación
	GLdouble x = 0;  //angulo girax

	void asignarValores();
	void rMatriz();
	void rMatrizInv();

};

