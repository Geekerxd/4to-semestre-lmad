#pragma once
#include "Images.h"
#include "Vector3.h"
#include <gl/GL.h>
#include <gl/GLU.h>


class spritesec: public Images, public Vector3
{
public:
	unsigned int _texture0;
	unsigned int _texture1;
	unsigned int _texture2;
	unsigned int _texture3;
	unsigned int _texture4;

	//char **p;
	/*
	char *anima[10] = { "assets/billboards/Arbol.png","assets/billboards/Arbol2.png",
	"assets/billboards/Arbol3.png" ,"assets/billboards/Arbol4.png","assets/billboards/Arbol.jpg" };
	*/

	WCHAR *AnimaPalm[15] = { L"assets/PalmAnima/palma_00.png",L"assets/PalmAnima/palma_01.png",
	L"assets/PalmAnima/palma_02.png",L"assets/PalmAnima/palma_01.png",L"assets/PalmAnima/palma_00.png"
	,L"assets/PalmAnima/palma_10.png",L"assets/PalmAnima/palma_11.png",L"assets/PalmAnima/palma_10.png" };

	float _width;
	float _height;

	Vector3 _up{ Vector3(0,1,0) };
	Vector3 _right;
	Vector3 _position;
	Vector3 _forward;
	
	int a=0;
	int count = 0;
	spritesec( HWND hWnd,float width, float height, Vector3 position, int b);


	~spritesec();

	void Draw(Vector3 position, float x, float y, float z);
	void SetAltitudPosition(float altitude);
	float GetAltitudY();
	Vector3 GetPosition();

};

