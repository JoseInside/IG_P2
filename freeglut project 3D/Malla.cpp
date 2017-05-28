#include "Malla.h"


Malla::Malla(int nV, int nN, int nC, PV3D** v, PV3D** n, Cara** c)
{
	numVertices = nV;
	numNormales = nN;
	numCaras = nC;
	vertice = v;
	normal = n;
	cara = c;
}


Malla::~Malla()
{
	for (int i = 0; i<numVertices; i++)
		delete vertice[i];
	delete[] vertice;

	for (int i = 0; i<numNormales; i++)
		delete normal[i];
	delete[] normal;

	for (int i = 0; i<numCaras; i++)
		delete cara[i];
	delete[] cara;
}

void Malla::dibuja(){
	
	//glMatrixMode(GL_MODELVIEW);
	glColor3f(0, 0, 1);
	for (int i = 0; i < numCaras; i++) {
		//glLineWidth(1.0);
		if(line)  glBegin(GL_LINE_LOOP);
		else if (!line) glBegin(GL_POLYGON); 

		for (int j = 0; j< cara[i]->getNumeroVertices(); j++) {

			int iN = cara[i]->getIndiceNormal(j);
			int iV = cara[i]->getIndiceVertice(j);
			glNormal3f(normal[iN]->getX(), normal[iN]->getY(), normal[iN]->getZ());
			//Si hubiera coordenadas de textura, aquí se suministrarían
			//las coordenadas de textura del vértice j con glTexCoor2f(…);
			glVertex3f(vertice[iV]->getX(), vertice[iV]->getY(), vertice[iV]->getZ());
		}
		glEnd();
	}


}
