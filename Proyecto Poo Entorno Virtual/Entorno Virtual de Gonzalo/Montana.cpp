#include "Montana.h"



Montana::Montana(char* path, char* path2,WCHAR texture[], WCHAR texture2[],
	float x, float y, float z, double ModelSize) 
	:x(x), y(y), z(z), ModelSize(ModelSize)
{
	_model = glmReadOBJ(path);
	_model2 = glmReadOBJ(path2);

	glmUnitize(_model);
	glmUnitize(_model2);

	Load(texture);
	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, GetWidth(), GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, GetPath());
	Unload();

	Load(texture2);
	glGenTextures(1, &_texture2);
	glBindTexture(GL_TEXTURE_2D, _texture2);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, GetWidth(), GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, GetPath());
	Unload();
}


Montana::~Montana()
{
	if (_model)
		delete _model;
	if (_model2)
		delete _model2;
}

void Montana::Draw()
{
	glPushMatrix();
	glPushAttrib(GL_CURRENT_BIT | GL_COLOR_BUFFER_BIT | GL_COLOR_MATERIAL);

	//glRotated(90, 0, 1, 0);
	glTranslated(x, y-50, z + 22);//+,-,0
	glScaled(this->ModelSize-20, this->ModelSize-20 , -this->ModelSize +20);
	glRotated(180, 0, 1, 0);

	glEnable(GL_CULL_FACE);



	glCullFace(GL_FRONT_FACE);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, _texture2);

	glmDraw(_model2, GLM_TEXTURE | GLM_SMOOTH);

	glDisable(GL_CULL_FACE);
	glPopAttrib();
	glPopMatrix();



	glPushMatrix();
	     glPushAttrib(GL_CURRENT_BIT | GL_COLOR_BUFFER_BIT | GL_COLOR_MATERIAL);
	     
	     //glRotated(90, 0, 1, 0);
	     glTranslated(x, y, z);
	     glScaled(this->ModelSize, this->ModelSize, -this->ModelSize);
	     glRotated(180, 0, 1, 0);
	     
	     glEnable(GL_CULL_FACE);
	     glEnable(GL_DEPTH_TEST);
	     glCullFace(GL_FRONT_FACE);
	     glEnable(GL_TEXTURE_2D);
	     
	     glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	     glBindTexture(GL_TEXTURE_2D, _texture);
	     
	     glmDraw(_model, GLM_TEXTURE | GLM_SMOOTH);
	     
	     glDisable(GL_CULL_FACE);
	     glPopAttrib();
	glPopMatrix();

	
}
