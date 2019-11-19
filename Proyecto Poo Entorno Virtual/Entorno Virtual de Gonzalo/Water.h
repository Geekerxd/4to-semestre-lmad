#pragma once
#include "Images.h"
#include <gl/GL.h>
#include <gl/GLU.h>
class Water: public Images
{
	unsigned int _texture;

	float cont2 = 16;
	bool aPress = true;

public:
	Water(WCHAR* texturePath);
	~Water(void);

	void Draw(float Alitud);
	void Update();
};

