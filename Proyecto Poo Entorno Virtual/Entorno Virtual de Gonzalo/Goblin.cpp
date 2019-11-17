#include "Goblin.h"



Goblin::Goblin(char* path, float x, float y, float z, double ModelSize)
	: x(x), y(y), z(z), ModelSize(ModelSize)
{
	_model = glmReadOBJ(path);
	glmUnitize(_model);
}
Goblin::Goblin(char* path, WCHAR texture[], float x, float y, float z, double ModelSize)
	: x(x), y(y), z(z), ModelSize(ModelSize)
{
	_model = glmReadOBJ(path);
	glmUnitize(_model);
	Load(texture);
	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, GetWidth(), GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, GetPath());
	Unload();
}


Goblin::~Goblin()
{
	if (_model)
		delete _model;
}

void Goblin::Draw(float x, float y, float z, int rot)
{
	_position.x = x;
	//_position.y = y;
	_position.z = z;

	glPushMatrix();
	glPushAttrib(GL_CURRENT_BIT | GL_COLOR_BUFFER_BIT | GL_COLOR_MATERIAL);

	glTranslated(_position.x, _position.y, _position.z);
	glRotated(rot, 0, 1, 0);
	glScaled(this->ModelSize, this->ModelSize, this->ModelSize);
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT_FACE);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, _texture);


	glmDraw(_model, GLM_TEXTURE | GLM_SMOOTH);

	glDisable(GL_CULL_FACE);
	glPopAttrib();
	glPopMatrix();
}

void Goblin::SetAltitudPosition(float altitude) {

	_position.y = altitude+10;

}
Vector3 Goblin::GetPosition()
{
	return _position;
}

void Goblin::rotate(float rot, int x, int y, int z) {
	glPushMatrix();
	glRotated(rot, x, y, z);
	glPopMatrix();
}
void Goblin::traslate(float x, float y, float z) {
	_position.x = x;
	_position.y = y;
	_position.z = z;
	glPushMatrix();

	glTranslated(_position.x, _position.y, _position.z);
	//printf("x= %f y= %f z= %f\n", _position.x, _position.y, _position.z);
	glPopMatrix();
}
