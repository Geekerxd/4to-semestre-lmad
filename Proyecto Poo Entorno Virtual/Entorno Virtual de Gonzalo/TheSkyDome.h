#pragma once

#include "Primitive.h"
#include "Images.h"
#include <gl/GL.h>
#include <gl/GLU.h>
//#include "glm.h"

class TheSkyDome :public Primitive, public Images
{
public:

	Mesh cuadro;
	//variables locales de la clase para contener los stacks y los slices de la esfera
	int st, sl;
	//el nombre numerico de la textura en cuestion, por lo pronto una
	unsigned int esferaTextura;

	TheSkyDome(HWND hWnd, int stacks, int slices, float radio, WCHAR nombre[]);
	~TheSkyDome();

	void Draw();
};

