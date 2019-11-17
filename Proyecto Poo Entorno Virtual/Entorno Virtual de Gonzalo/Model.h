#pragma once
#include "glm.h"
#include "Images.h"
class Model: public Images
{
private: 
	GLMmodel* _model;
	unsigned int _texture;

	double ModelSize{1};
	float x;
	float y;
	float z;
public:
	Model(char* path, float x, float y, float z, double ModelSize);
	Model(char* path, WCHAR texture[], float x, float y, float z, double ModelSize);
	~Model();

	void Draw();
};

