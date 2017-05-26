#pragma once
#include <GL/freeglut.h>
//#include <cmath>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "PV3D.h"
#include "Cara.h"

class Malla
{
protected:

		int numVertices;
		PV3D** vertice;
		int numNormales; //=numCaras, frecuentemente
		PV3D** normal;
		int numCaras;
		Cara** cara;

		PV3D* vertActual;
		PV3D* vertSiguiente;
public:
	Malla(int nV, int nN, int nC, PV3D** v, PV3D** n, Cara** c);
	Malla() {};
	~Malla();

		void dibuja();
		int getNumeroVertices() { return numVertices; }
		int getNumeroNormales() { return numNormales; }
		int getNumeroCaras() { return numCaras; }

	
};

