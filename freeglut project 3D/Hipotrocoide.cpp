#include "Hipotrocoide.h"

Hipotrocoide::Hipotrocoide(int nP, int nQ, GLfloat a, GLfloat b, GLfloat c) : nP(nP), nQ(nQ), a(a), b(b), c(c)
{
	a = a;
	b = b;
	c = c;
	nP = nP;	//m
	nQ = nQ;	//n
	
	r = 7;

	numVertices = nP*nQ;
	numCaras = nQ *(nP - 1);
	numNormales = numCaras;

	//Se crean los arrays de vértices, normales y caras
	vertice = new PV3D*[numVertices];
	normal = new PV3D*[numNormales];
	cara = new Cara*[numCaras];

	t = 0.0f;

	// se crea el perfil
	perfil = new PV3D*[nP];
	GLfloat inc = (2 * 3,1416 / nP);
	for (int i = 0; i<nP; i++)
		perfil[i] = new PV3D(r*cos(i*inc), r*sin(i*inc), 0, 1);
	//calculamos la matriz
	rMatriz(t);
	
	
	
	//Crear vértices iniciales (rellenas vértices)
	for (int j = 0; j < nP; j++) 
		vertice[j] = perfil[j]->clona();

	//Vertices de la malla
	for (int i = 1; i < nQ; i++){ //generar el perfil i-ésimo
		t = i * 360 / (double)nQ;	//Aumentamos t
		double c = cos(t);
		double s = sin(t);
		
		//R_y es la matriz de rotación sobre el eje Y
		for (int j = 0; j < nP; j++) {
			int indice = i * nP + j;
			//Transformar el punto j-ésimo del perfil original
			PV3D* p = C(t);
			double x = c*perfil[j]->getX() + s*perfil[j]->getZ();
			double z = -s*perfil[j]->getX() + c*perfil[j]->getZ();
			p = new PV3D(x, perfil[j]->getY(), z, 1);
			vertice[indice] = p;
			
		} //for
	} //for

	//Construcción de las caras
	int indiceCara = 0;
	for (int i = 0; i < nQ; i++){ //unir el perfil i-ésimo con el (i+1)%n-ésimo
		for (int j = 0; j < nP - 1; j++) { //esquina inferior-izquierda de una cara
			indiceCara = i*(nP-1) + j;
			int indice = i * nP + j;
			VerticeNormal** vn = new VerticeNormal*[4];
			vn[0] = new VerticeNormal(indice, indiceCara);
			vn[1] = new VerticeNormal((indice + nP) % numVertices, indiceCara);
			vn[2] = new VerticeNormal((indice + 1 + nP) % numVertices, indiceCara);
			vn[3] = new VerticeNormal(indice + 1, indiceCara);
			cara[indiceCara] = new Cara(4, vn);

			PV3D* v = calculoVectorNormal(cara[indiceCara]); //Newell
			normal[indiceCara] = v;
			indiceCara++;
		} //for
	} //for
	
}

Hipotrocoide::~Hipotrocoide()
{
}


PV3D * Hipotrocoide::C(GLfloat t) {
	((a - b)*cos(t) + c*cos(t*((a - b) / b)), 0, (a - b)*sin(t) - c*sin(t*((a - b) / b)));
	PV3D* p = new PV3D(a, b, c, 1);
	return p;
};

PV3D * Hipotrocoide::C’(GLfloat t) {
	((a - b)*-sin(t) + c*-sin(t*((a - b) / b)), 0, (a - b)*cos(t) - c*cos(t*((a - b) / b)));
	PV3D* p = new PV3D(a, b, c, 1);
	return p;
};

PV3D * Hipotrocoide::C’’(GLfloat t) {
	((a - b)*-cos(t) + c*-cos(t*((a - b) / b)), 0, (a - b)*-sin(t) - c*-sin(t*((a - b) / b)));
	PV3D* p = new PV3D(a, b, c, 1);
	return p;
};

	// se coje el clonado sino cogerias siempre el del mismo punto (B, T y N)
PV3D * Hipotrocoide::T(GLfloat t) {

	PV3D* p = C’(t);
	p->normaliza(p->getX(), p->getY(), p->getZ());
	return p;
};
PV3D * Hipotrocoide::B(GLfloat t) {
	PV3D* p = T(t);
	PV3D* p2 = C’’(t);
	p2 = p2->normaliza(p2->getX(), p2->getY(), p2->getZ());
	p = p->productoVectorial(p2);
	return p;
};
PV3D * Hipotrocoide::N(GLfloat t) {
	
	PV3D* p = B(t);
	PV3D* p2 = T(t);

	p = p->productoVectorial(p2);
	return p;
};
//se usa un metodo para rellenar la matriz en el angulo 0 para iniciarla
void Hipotrocoide::rMatriz(GLfloat t) {

	PV3D* n = N(t);
	PV3D* b = B(t);
	PV3D* tp = T(t);
	PV3D* c = C(t);

	/// (N,B,T,C)
	m[0] = n->getX();
	m[1] = n->getY();
	m[2] = n->getZ();
	m[3] = 0;

	m[4] = b->getX();
	m[5] = b->getY();
	m[6] = b->getZ();
	m[7] = 0;

	m[8] = tp->getX();
	m[9] = tp->getY();
	m[10] = tp->getZ();
	m[11] = 0;

	m[12] = c->getX();
	m[13] = c->getY();
	m[14] = c->getZ();
	m[15] = 1;

	delete n;
	delete b;
	delete tp;
	delete c;
}

//el calculo de vN por newell va en la clase donde lo usas para no liarte con punteros ni mierdas que ya hay bastantes
PV3D* Hipotrocoide::calculoVectorNormal(Cara* c) {

	float n[3] = { 0, 0, 0 };
	PV3D* vertActual;
	PV3D* vertSiguiente;

	for (int i = 0; i < c->getNumeroVertices(); i++) {
		vertActual = vertice[c->getIndiceVertice(i)];
		vertSiguiente = vertice[c->getIndiceVertice((i + 1) % c->getNumeroVertices())];

		n[0] += (vertActual->getY() - vertSiguiente->getY())*
			(vertActual->getZ() + vertSiguiente->getZ());
		n[1] += (vertActual->getZ() - vertSiguiente->getZ())*
			(vertActual->getX() + vertSiguiente->getX());
		n[2] += (vertActual->getX() - vertSiguiente->getX())*
			(vertActual->getY() + vertSiguiente->getY());
	}

	PV3D* nNormal = new PV3D(n[0], n[1], n[2], 0);
	nNormal->normaliza(n[0], n[1], n[2]);
	return nNormal;

}

