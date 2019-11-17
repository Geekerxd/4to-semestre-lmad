#pragma once

#include "Vector3.h"


struct Vertex {
	float posX, posY, posZ;
	float normX, normY, normZ;
	float u, v;
};

struct Mesh {
	Vertex* mesh;
	unsigned int* indexes;
	void Unload() {



		if (mesh)
			delete mesh;
		if (indexes)
			delete indexes;
	}
};

class Primitive: public Vector3
{
public:
	Primitive();

	Mesh Sphere(int stack, int slices, float radius, float start, float end);
	Mesh Plane(int vertexX, int vertexZ, float width, float depth);
	Mesh Plane(int vertexX, int vertexZ, float width, float depth, unsigned char* height, float tile = 1);
};

