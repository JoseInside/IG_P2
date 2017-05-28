#pragma once
#include "Malla.h"


class Hipotrocoide : public Malla
{
public:
	Hipotrocoide(int nP, int nQ, GLfloat a, GLfloat b, GLfloat c);
	~Hipotrocoide();

	GLfloat a, b ,c;  //parametros de la curva
	int nP; //n�mero de lados del pol�gono que aproxima el grosor de la curva (numero de puntos en el perfil)
	int nQ; // n�mero de muestras que se toman en la curva (numero de rotaciones) 
	float r;
	double t; // ANGULO
	GLfloat m[16];  //matriz para pasar el perfil a la curva

	PV3D** perfil; // pol�gono de nP lados

	//METODOS

	PV3D* C(GLfloat t), * C2(GLfloat t),* C3(GLfloat t),* T(GLfloat t),* B(GLfloat t),* N(GLfloat t);// m�todos necesarios para rellenar la matriz m

	PV3D* calculoVectorNormal(Cara* c);

	void rMatriz(GLfloat t); // rellena la matriz 
};

