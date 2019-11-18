#include "spritesec.h"

#include <iostream>
using namespace std;

spritesec::spritesec(HWND hWnd,
	float width, float height, Vector3 position,int b) :_width(width), _height(height), _position(position)
{
	Load(AnimaPalm[b]);
	glGenTextures(1, &_texture1);
	glBindTexture(GL_TEXTURE_2D, _texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, GetWidth(), GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, GetPath());
	Unload();


}


spritesec::~spritesec()
{
	//_position.y = 50;

	glDeleteTextures(1, &_texture1);
	
	glDeleteTextures(1, &_texture1);
	glDeleteTextures(1, &_texture2);
	glDeleteTextures(1, &_texture3);
	glDeleteTextures(1, &_texture4);
}

void spritesec::Draw(Vector3 position, float x, float y, float z)
{
	//_position.x = x;
	//_position.y = y;
	//_position.z = z;

	glPushMatrix();
	glTranslated(x, y, z);
	glScaled(0.2, 0.2, 0.2);
	
	//habilitamos el culling para reducir tiempo de procesamiento de las texturas
	//las texturas se analizan pixel a pixel para determinar que se imprimen o no
	//por lo que aunque no la veamos nos costo, por eso la eliminamos.
	glEnable(GL_CULL_FACE);
	//hay dos tipos de cull el frontal y el trasero (back)
	glCullFace(GL_FRONT);
	//habilitamos la textura, podriamos mezclar colores y cambiar la tonalidad de la textura
	//con glColorxf
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, _texture1);
	//calculamos el vector de la camara al billboard
	_forward = Vector3(position.x - _position.x-x, position.y - _position.y-y, position.z - _position.z-z);
	//obtenemos 
	_right = Normalize(Cross(_up, _forward));
	_right.x *= GetWidth() / 2.0;

	_right.z *= GetWidth() / 2.0;

	glBegin(GL_QUADS);
	
	glTexCoord2f(0, 0);
	glVertex3f(_position.x - _right.x, _position.y + GetHeight(), _position.z - _right.z);

	glTexCoord2f(1, 0);
	glVertex3f(_position.x + _right.x, _position.y + GetHeight(), _position.z + _right.z);

	glTexCoord2f(1, 1);
	glVertex3f(_position.x + _right.x, 0, _position.z + _right.z);

	glTexCoord2f(0, 1);
	glVertex3f(_position.x - _right.x, 0, _position.z - _right.z);

	glEnd();
	
	glDisable(GL_CULL_FACE);
	glDisable(GL_ALPHA);
	glDisable(GL_BLEND);

	//glPushAttrib(GL_CURRENT_BIT | GL_COLOR_BUFFER_BIT | GL_COLOR_MATERIAL);
	

	glPopMatrix();

}
void spritesec::SetAltitudPosition(float altitude) {

	_position.y = altitude + 10;

}
float spritesec::GetAltitudY() {
	return _position.y;
}
Vector3 spritesec::GetPosition()
{
	return _position;
}
