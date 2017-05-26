#pragma once
class VerticeNormal
{
public:
	VerticeNormal(int indiceVertice, int indiceNormal);
	~VerticeNormal();

	int getIndiceVertice() { return indiceVertice_; }
	int	getIndiceNormal() { return indiceNormal_; }

private:
	int indiceVertice_, indiceNormal_;
};

