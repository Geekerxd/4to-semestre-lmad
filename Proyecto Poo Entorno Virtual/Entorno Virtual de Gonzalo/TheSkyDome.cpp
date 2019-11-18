#include "TheSkyDome.h"



TheSkyDome::TheSkyDome(HWND hWnd, int stacks, int slices, float radio, WCHAR nombre[])
{
	this->hWnd = hWnd;
	cuadro = Sphere(stacks, slices, radio, 0.5, 1);
	st = stacks;
	sl = slices;
	//cargamos la textura de la figura
	Load(nombre);
	//en caso del puntero de la imagen sea nulo se brica esta opcion
	if (GetPath())
	{
		glGenTextures(1, &esferaTextura);
		glBindTexture(GL_TEXTURE_2D, esferaTextura);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, GetWidth(), GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, GetPath());
		//disponemos la textura del gdi.
		Unload();
	}
}


TheSkyDome::~TheSkyDome()
{
	//nos aseguramos de disponer de los recursos previamente reservados
	delete cuadro.mesh;
	delete cuadro.indexes;
	glDeleteTextures(1, &esferaTextura);
}


void TheSkyDome:: Draw()
{
	int ind = 0;
	int indice;

	//habilitamos el culling para reducir tiempo de procesamiento de las texturas
	//las texturas se analizan pixel a pixel para determinar que se imprimen o no
	//por lo que aunque no la veamos nos costo, por eso la eliminamos.
	glEnable(GL_CULL_FACE);
	//hay dos tipos de cull el frontal y el trasero (back)
	glCullFace(GL_BACK);

	glDisable(GL_DEPTH_TEST);
	//habilitamos la textura, podriamos mezclar colores y cambiar la tonalidad de la textura
	//con glColorxf
	

	glEnable(GL_TEXTURE_2D);
	//usamos modulate para que la textura sea afectada por el valor de la normal en cuanto
	//a luz
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, esferaTextura);
	//habilitamos la posibilidad de guardar arreglos de procesamiento inmediato
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//asignamos punteros de vertices, normales y texturas al buffer de conexiones que sigue
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &cuadro.mesh[0].posX);
	glNormalPointer(GL_FLOAT, sizeof(Vertex), &cuadro.mesh[0].normX);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &cuadro.mesh[0].u);

	//conectamos todos los vertices previamente cargados a traves de sus punteros para procesarse
	glDrawElements(GL_TRIANGLES, (sl - 1)*(st - 1) * 6, GL_UNSIGNED_INT, cuadro.indexes);
	//desocupamos la asignacion para que podamos utilizarlo con un nuevo elemento
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glColor3f(1, 1, 0);
}