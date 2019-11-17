#pragma once
#include "Images.h"
#include "Vector3.h"
#include <gl/GL.h>
#include <gl/GLU.h>
class Billboard: public Images, public Vector3
{
public:
	float _width;
	float _height;
	Vector3 _up{Vector3(0,1,0)};
	Vector3 _right;
	Vector3 _position;
	Vector3 _forward;

	unsigned int _texture;

	Billboard(HWND hWnd, WCHAR texture[], float width, float height, Vector3 position);

	~Billboard();

	void Draw(Vector3 position);
};

