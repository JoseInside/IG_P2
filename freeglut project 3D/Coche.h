#pragma once
#include <GL/freeglut.h>
#include <gl/GLU.h>
#include <gl/GL.h>
class Coche
{
public:
	Coche(int tamCoche, int baseRadius, int topRadius, int height, int slices, int stacks, GLfloat vel) :_tamCoche(tamCoche),
		_baseRadius(baseRadius), _topRadius(topRadius), _height(height), _slices(slices), _stacks(stacks), _vel(vel) {}
	~Coche();
	
	//glutSolidCube(tamCoche);
	//q = gluNewQuadric();

	//gluCylinder(q, _baseRadius, _topRadius, _height, _slices, _stacks);

	void dibujaCoche(GLfloat girRueda, GLUquadricObj * q);
	GLfloat girRueda;
	
private:
	GLUquadricObj* q;
	GLfloat _vel;
	int _tamCoche;
	int _baseRadius;
	int _topRadius;
	int _height;
	int _slices;
	int _stacks;
	float g;
};

