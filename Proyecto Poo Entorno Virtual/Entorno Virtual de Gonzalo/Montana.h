#pragma once
#include "Images.h"
#include "glm.h"
class Montana :
	public Images
{
private:
	GLMmodel* _model;
	unsigned int _texture;

	GLMmodel* _model2;
	unsigned int _texture2;
	double ModelSize{ 1 };
	float x;
	float y;
	float z;
public:
	Montana(char* path, char* path2,
		WCHAR texture[], WCHAR texture2[],
		float x, float y, float z, double ModelSize);
	~Montana();
	struct Collition;
	void Draw();
};

