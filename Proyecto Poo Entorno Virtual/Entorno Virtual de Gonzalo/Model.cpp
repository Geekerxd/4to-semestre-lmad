#include "Model.h"

Model::Model(char* path, float x, float y, float z, double ModelSize)
	: x(x), y(y), z(z), ModelSize(ModelSize)
{
	_model = glmReadOBJ(path);
	glmUnitize(_model);
}

Model::Model(char* path, WCHAR texture[], float x, float y, float z, double ModelSize)
	:x(x), y(y), z(z), ModelSize(ModelSize)
{
	_model = glmReadOBJ(path);
	glmUnitize(_model);
	Load(texture);
	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, GetWidth(), GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, GetPath());
	Unload();
}

Model::~Model()
{
	if (_model)
		delete _model;
}

void Model::Draw()
{
	glPushMatrix();
	    glPushAttrib(GL_CURRENT_BIT | GL_COLOR_BUFFER_BIT | GL_COLOR_MATERIAL);

//glRotated(90, 0, 1, 0);
	        glTranslated(x, y, z);
	        glScaled(this->ModelSize, this->ModelSize, -this->ModelSize);
			glRotated(90, 0, 1, 0);

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
