#pragma once
#include "glm.h"
#include "Images.h"
#include "Vector3.h"

class key: public Images
{
private:
	GLMmodel* _model;
	unsigned int _texture;

	double ModelSize{ 1 };
	float x;
	float y;
	float z;
	Vector3 _position{ Vector3(-607,10,0) };

public:
	key(char* path, WCHAR texture[]);
	~key();
	Vector3 GetPosition();
	void Draw(float x, float y, float z, float Sx, float Sy, float Sz, float angle,
		int Rx, int Ry, int Rz);
};

