#pragma once
#include "VerticeNormal.h"

class Cara
{
public:
	Cara(int nV, VerticeNormal** vN);
	~Cara();

	int getNumeroVertices() { return numVertices; }
	int getIndiceNormal(int i) { return arrayVN[i]->getIndiceNormal(); }
	int getIndiceVertice(int i) { return arrayVN[i]->getIndiceVertice(); }

private:
	int numVertices;
	VerticeNormal** arrayVN;
};

