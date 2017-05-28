#pragma once
#include <GL/freeglut.h>
#include <gl/GLU.h>
#include <gl/GL.h>
class Coche
{
public:
	Coche(int tamCoche, int baseRadius, int topRadius, int height, int slices, int stacks) :_tamCoche(tamCoche),
		_baseRadius(baseRadius), _topRadius(topRadius), _height(height), _slices(slices), _stacks(stacks) {}
	~Coche();
	
	//glutSolidCube(tamCoche);
	//q = gluNewQuadric();

	//gluCylinder(q, _baseRadius, _topRadius, _height, _slices, _stacks);

	void dibujaCoche();
	
private:
	GLUquadricObj* q;
	GLfloat girRueda;
	int _tamCoche;
	int _baseRadius;
	int _topRadius;
	int _height;
	int _slices;
	int _stacks;
};

