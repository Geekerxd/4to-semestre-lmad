#pragma once
#include <windows.h>
#include "Images.h"
#include "Primitive.h"
#include <gl/GL.h>
#include <gl/GLU.h>

class Terrain: public Primitive, public Images
{
private:
	float _width{ 0 };
	float _depth{ 0 };
	float _deltaX{ 0 };
	float _deltaZ{ 0 };
public:
	Mesh terrain;
	int vertexX, vertexZ;
	unsigned int planeText;

	Terrain(HWND hWnd, WCHAR height[], WCHAR text[], float width, float depth);
	~Terrain();
	void Draw();
	float Surface(float x, float z);

};

