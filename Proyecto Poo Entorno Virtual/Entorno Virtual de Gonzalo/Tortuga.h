#pragma once
#include "Images.h"
#include "glm.h"
#include "Vector3.h"
class Tortuga :
	public Images
{
private:
	GLMmodel* _model;
	unsigned int _texture;

	double ModelSize{ 1 };
	float x;
	float y;
	float z;
	Vector3 _position{ Vector3(0,0,0) };

public:
	Tortuga(char* path, WCHAR texture[]);
	~Tortuga();
	Vector3 GetPosition();
	void Draw(float x, float y, float z, float Sx, float Sy, float Sz, float angle,
		int Rx, int Ry, int Rz);
};



