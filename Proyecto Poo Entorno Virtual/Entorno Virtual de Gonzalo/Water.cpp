#include "Water.h"
#include <iostream>
using namespace std;
Water::Water(WCHAR* texturePath)
{
	Load(texturePath);
	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, GetWidth(), GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, GetPath());
	Unload();
}


Water::~Water(void)
{
	glDeleteTextures(1, &_texture);
}

void Water::Draw()
{
	glPushAttrib(GL_CURRENT_BIT | GL_TEXTURE_BIT);
	glBindTexture(GL_TEXTURE_2D, _texture);

	// U V
	static float water_factor_min = 0.0f;
	static float water_factor_max = 20.0f;
	static float water_size = 800;
	static double modifier = 0;
	float altura = 15.f;
	// water_factor_min += 1;
	modifier += .01;





	//cout << cont2<< endl;
	
	if (water_factor_max > 30) { aPress = false; /*rotate = -90;*/ }

	if (water_factor_max < 16) { aPress = true;/* rotate = 90;*/ }

	if (aPress == true) {
		//cont2+=0.1;
		water_factor_max += 00.05;
		
	}
	else { //cont2-=0.1;
	
	water_factor_max -= 00.05;
	}
	


	glBegin(GL_QUADS);
	glTexCoord2f(water_factor_min, water_factor_min);
	glColor4f(0.1f, 0.3f, 0.6f, 0.2f);
	glVertex3f(-water_size, altura, water_size);

	glTexCoord2f(water_factor_max, water_factor_min);
	glColor4f(0.1f, 0.3f, 0.6f, 0.2f);
	glVertex3f(water_size, altura, water_size);

	glTexCoord2f(water_factor_max, water_factor_max);
	glColor4f(0.1f, 0.3f, 0.6f, 0.2f);
	glVertex3f(water_size, altura, -water_size);

	glTexCoord2f(water_factor_min, water_factor_max);
	glColor4f(0.1f, 0.3f, 0.6f, 0.2f);
	glVertex3f(-water_size, altura, -water_size);
	glEnd();
	glPopAttrib();
}
