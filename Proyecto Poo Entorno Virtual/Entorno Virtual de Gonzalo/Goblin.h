#pragma once
#include "glm.h"
#include "Images.h"
#include "Vector3.h"

class Goblin : public Images
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
	Goblin(char* path, float x, float y, float z, double ModelSize);
	Goblin(char* path, WCHAR texture[], float x, float y, float z, double ModelSize);
	~Goblin();

	void Draw(float x, float y, float z,int rot);
	void SetAltitudPosition(float altitude);
	Vector3 GetPosition();
	void rotate(float rot,int x,int y,int z);
	void traslate(float x, float y,float z);
};

