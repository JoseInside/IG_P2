#include "Hipotrocoide.h"

Hipotrocoide::Hipotrocoide(int nP, int nQ, GLfloat a, GLfloat b, GLfloat c) : nP(nP), nQ(nQ), a(a), b(b), c(c)
{
	this->a = a;
	this->b = b;
	this->c = c;
	this->nP = nP;	//m
	this->nQ = nQ;	//n
	
	r = 0.5;

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
	GLfloat inc = (2.0f * 3.1416f / nP);
	for (int i = 0; i < nP; i++) {
		perfil[i] = new PV3D(r*cos(i*inc), r*sin(i*inc), 0, 1);
	}
	//calculamos la matriz
	rMatriz(t);
	
	//Crear vértices iniciales (rellenas vértices)
	for (int j = 0; j < nP; j++) {
		PV3D* aux = new PV3D (0, 0, 0, 1);
		aux->x = m[0] * perfil[j]->getX() + m[4] * perfil[j]->getY() + m[8] * perfil[j]->getZ() + m[12];
		aux->y = m[1] * perfil[j]->getX() + m[5] * perfil[j]->getY() + m[9] * perfil[j]->getZ() + m[13];
		aux->z = m[2] * perfil[j]->getX() + m[6] * perfil[j]->getY() + m[10] * perfil[j]->getZ() + m[14];
	
		vertice[j] = aux;
		//vertice[j] = perfil[j]->clona();
	}

	//Vertices de la malla
	for (int i = 1; i < nQ; i++){ //generar el perfil i-ésimo
		//t = i * 360 / (double)nQ;	//Aumentamos t
		t = (8.0f * 3.1416f * i) / (double)nQ;
		double c = cos(t);
		double s = sin(t);
		rMatriz(t);
		//R_y es la matriz de rotación sobre el eje Y
		for (int j = 0; j < nP; j++) {
			int indice = i * nP + j;
			//Transformar el punto j-ésimo del perfil original
			/*PV3D* p = C(t);
			double x = c*perfil[j]->getX() + s*perfil[j]->getZ();
			double z = -s*perfil[j]->getX() + c*perfil[j]->getZ();
			p = new PV3D(x, perfil[j]->getY(), z, 1);
			vertice[indice] = p;
			*/
			GLfloat x = m[0] * perfil[j]->getX() + m[4] * perfil[j]->getY() + m[8] * perfil[j]->getZ() + m[12];
			GLfloat y = m[1] * perfil[j]->getX() + m[5] * perfil[j]->getY() + m[9] * perfil[j]->getZ() + m[13];
			GLfloat z = m[2] * perfil[j]->getX() + m[6] * perfil[j]->getY() + m[10] * perfil[j]->getZ() + m[14];
			PV3D* aux = new PV3D(x, y, z, 1);

			vertice[indice] = aux;
			
		} //for
	} //for

	//Construcción de las caras
	int indiceCara = 0;
	for (int i = 0; i < nQ; i++){ //unir el perfil i-ésimo con el (i+1)%n-ésimo
		for (int j = 0; j < nP-1; j++) { //esquina inferior-izquierda de una cara
			//indiceCara = i*(nP) + j;
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
	
	GLfloat _a, _b, _c;

	_a = ((a - b)*cos(t) + c*cos(t*((a - b) / b)));
	_b = 0;
	_c = (a - b)*sin(t) - c*sin(t*((a - b) / b));
	
	PV3D* p = new PV3D(_a, _b, _c, 1);

	return p;
};

PV3D * Hipotrocoide::C2(GLfloat t) {
	/*((a - b)*-sin(t) + c*-sin(t*((a - b) / b)), 0, (a - b)*cos(t) - c*cos(t*((a - b) / b)));
	PV3D* p = new PV3D(a, b, c, 1);
	return p;*/
	return new PV3D(-(a - b) * sin(t) - c * sin(((a - b) / b) * t) * ((a - b) / b), 0.0f, (a - b) * cos(t) - c * cos(((a - b) / b) * t) * ((a - b) / b), 0);
};

PV3D * Hipotrocoide::C3(GLfloat t) {
	/*((a - b)*-cos(t) + c*-cos(t*((a - b) / b)), 0, (a - b)*-sin(t) - c*-sin(t*((a - b) / b)));
	PV3D* p = new PV3D(a, b, c, 1);
	return p;*/
	return new PV3D(-(a - b) * cos(t) - c * cos(((a - b) / b) * t) * ((a - b) / b) * ((a - b) / b), 0.0f, -(a - b) * sin(t) + c * sin(((a - b) / b) * t) * ((a - b) / b) * ((a - b) / b), 0);

};

	// se coje el clonado sino cogerias siempre el del mismo punto (B, T y N)
PV3D * Hipotrocoide::T(GLfloat t) {
	PV3D * aux = C2(t)->clona();
	aux = aux->normaliza(aux->x, aux->y, aux->z);
	return aux;
	/*PV3D* p = C2(t);
	p->normaliza(p->getX(), p->getY(), p->getZ());
	return p;*/
};
PV3D * Hipotrocoide::B(GLfloat t) {
	PV3D* aux = C2(t)->clona();
	PV3D *aux2 = aux->productoVectorial(C3(t)->clona());
	aux2 = aux2->normaliza(aux2->x, aux2->y, aux2->z);
	delete aux;
	return aux2;
	/*PV3D* p = T(t);
	PV3D* p2 = C3(t);
	p2 = p2->normaliza(p2->getX(), p2->getY(), p2->getZ());
	p = p->productoVectorial(p2);
	return p;*/
};
PV3D * Hipotrocoide::N(GLfloat t) {
	
	PV3D * b = B(t)->clona();
	return b->productoVectorial(T(t)->clona());

	/*PV3D* p = B(t);
	PV3D* p2 = T(t);

	p = p->productoVectorial(p2);
	return p;*/
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

	float n1 = 0, n2 = 0, n3 = 0;
	PV3D* vertActual;
	PV3D* vertSiguiente;

	for (int i = 0; i < c->getNumeroVertices(); i++) {
		vertActual = vertice[c->getIndiceVertice(i)];
		vertSiguiente = vertice[c->getIndiceVertice((i + 1) % c->getNumeroVertices())];

		n1 += (vertActual->getY() - vertSiguiente->getY())*
			(vertActual->getZ() + vertSiguiente->getZ());
		n2 += (vertActual->getZ() - vertSiguiente->getZ())*
			(vertActual->getX() + vertSiguiente->getX());
		n3 += (vertActual->getX() - vertSiguiente->getX())*
			(vertActual->getY() + vertSiguiente->getY());
	}

	PV3D* nNormal = new PV3D(n1, n2, n3, 0);
	nNormal = nNormal->normaliza(n1, n2, n3);
	return nNormal;
	
}

