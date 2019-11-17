#include "Terrain.h"


Terrain::Terrain(HWND hWnd, WCHAR height[], WCHAR texture[], float width, float depth)
{
	_width = width;
	_depth = depth;
	//cargamos la textura de la figura
	Load(height);
	    //en caso del puntero de la imagen sea nulo se brica esta opcion
	    terrain = Plane(GetWidth(), GetHeight(), width, depth, GetPath(), 10);//10 es cuantas veces se repite
	    _deltaX = _width / GetWidth();
	    _deltaZ = _depth / GetHeight();
	    vertexX = GetWidth();
	    vertexZ = GetHeight();
	    //disponemos la textura del gdi.
	    Unload();
	Load(texture);
	    glGenTextures(1, &planeText);
	    glBindTexture(GL_TEXTURE_2D, planeText);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, GetWidth(), GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, GetPath());
	Unload();
}

Terrain::~Terrain()
{
	terrain.Unload();
	glDeleteTextures(1, &planeText);
}

void Terrain::Draw()
{
	glPushMatrix();
	    glPushAttrib(GL_CURRENT_BIT | GL_COLOR_BUFFER_BIT | GL_COLOR_MATERIAL);
	         int ind = 0;
	         int indice;
	         
	         //habilitamos el culling para reducir tiempo de procesamiento de las texturas
	         //las texturas se analizan pixel a pixel para determinar que se imprimen o no
	         //por lo que aunque no la veamos nos costo, por eso la eliminamos.
	         glEnable(GL_CULL_FACE);
	             //hay dos tipos de cull el frontal y el trasero (back)
	             glCullFace(GL_BACK);
	             //habilitamos la textura, podriamos mezclar colores y cambiar la tonalidad de la textura
	             //con glColorxf
	             glEnable(GL_TEXTURE_2D);
	             //usamos modulate para que la textura sea afectada por el valor de la normal en cuanto
	             //a luz
	             glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	             
	             glBindTexture(GL_TEXTURE_2D, planeText);
	             //habilitamos la posibilidad de guardar arreglos de procesamiento inmediato
	             glEnableClientState(GL_VERTEX_ARRAY);
	             glEnableClientState(GL_NORMAL_ARRAY);
	             glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	             
	             //asignamos punteros de vertices, normales y texturas al buffer de conexiones que sigue
	             glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &terrain.mesh[0].posX);
	             glNormalPointer(GL_FLOAT, sizeof(Vertex), &terrain.mesh[0].normX);
	             glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &terrain.mesh[0].u);
	             
	             GLfloat wm[16];
	             glGetFloatv(GL_MODELVIEW_MATRIX, wm);
	             
	             //conectamos todos los vertices previamente cargados a traves de sus punteros para procesarse
	             glDrawElements(GL_TRIANGLES, (vertexX - 1) * (vertexZ - 1) * 6, GL_UNSIGNED_INT, terrain.indexes);
	             //desocupamos la asignacion para que podamos utilizarlo con un nuevo elemento
	             glDisableClientState(GL_VERTEX_ARRAY);
	             glDisableClientState(GL_NORMAL_ARRAY);
	             glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	         glDisable(GL_CULL_FACE);
	    glPopAttrib();
	glPopMatrix();
}

float Terrain::Surface(float x, float z)
{
	//obtenemos el indice pero podria incluir una fraccion
	float indexfX = (x + _width / 2) / _deltaX;
	float indexfZ = (z + _depth / 2) / _deltaZ;
	//nos quedamos con solo la parte entera del indice
	int indexX = (int)indexfX;
	int indexZ = (int)indexfZ;
	//nos quedamos con solo la fraccion del indice
	float difx = indexfX - indexX;
	float difz = indexfZ - indexZ;

	float height;
	float D;

	//el cuadro del terrain esta formado por dos triangulos, si difx es mayor que dify 
	//entonces estamos en el triangulo de abajo en caso contrario arriba
	if (difx > difz)
	{
		//obtenemos el vector 1 de dos que se necesitan
		Vector3 v1(terrain.mesh[indexX + 1 + (indexZ + 1) * vertexX].posX - terrain.mesh[indexX + indexZ * vertexX].posX,
			terrain.mesh[indexX + 1 + (indexZ + 1) * vertexX].posY - terrain.mesh[indexX + indexZ * vertexX].posY,
			terrain.mesh[indexX + 1 + (indexZ + 1) * vertexX].posZ - terrain.mesh[indexX + indexZ * vertexX].posZ);
		//obtenemos el vector 2 de dos
		Vector3 v2(terrain.mesh[indexX + 1 + indexZ * vertexX].posX - terrain.mesh[indexX + indexZ * vertexX].posX,
			terrain.mesh[indexX + 1 + indexZ * vertexX].posY - terrain.mesh[indexX + indexZ * vertexX].posY,
			terrain.mesh[indexX + 1 + indexZ * vertexX].posZ - terrain.mesh[indexX + indexZ * vertexX].posZ);

		//con el producto punto obtenemos la normal y podremos obtener la ecuacion del plano
		//la parte x de la normal nos da A, la parte y nos da B y la parte z nos da C
		Vector3 normalPlano = Cross(v1, v2);
		//entonces solo falta calcular D
		D = -1 * (normalPlano.x * terrain.mesh[indexX + indexZ * vertexX].posX +
			normalPlano.y * terrain.mesh[indexX + indexZ * vertexX].posY +
			normalPlano.z * terrain.mesh[indexX + indexZ * vertexX].posZ);
		//sustituyendo obtenemos la altura de contacto en el terrain
		height = ((-normalPlano.x * x - normalPlano.z * z - D) / normalPlano.y);
	}
	else
	{
		Vector3 v1(terrain.mesh[indexX + (indexZ + 1) * vertexX].posX - terrain.mesh[indexX + indexZ * vertexX].posX,
			terrain.mesh[indexX + (indexZ + 1) * vertexX].posY - terrain.mesh[indexX + indexZ * vertexX].posY,
			terrain.mesh[indexX + (indexZ + 1) * vertexX].posZ - terrain.mesh[indexX + indexZ * vertexX].posZ);

		Vector3 v2(terrain.mesh[indexX + 1 + (indexZ + 1) * vertexX].posX - terrain.mesh[indexX + indexZ * vertexX].posX,
			terrain.mesh[indexX + 1 + (indexZ + 1) * vertexX].posY - terrain.mesh[indexX + indexZ * vertexX].posY,
			terrain.mesh[indexX + 1 + (indexZ + 1) * vertexX].posZ - terrain.mesh[indexX + indexZ * vertexX].posZ);


		Vector3 normalPlane = Cross(v1, v2);

		D = -1 * (normalPlane.x * terrain.mesh[indexX + indexZ * vertexX].posX +
			normalPlane.y * terrain.mesh[indexX + indexZ * vertexX].posY +
			normalPlane.z * terrain.mesh[indexX + indexZ * vertexX].posZ);

		height = ((-normalPlane.x * x - normalPlane.z * z - D) / normalPlane.y);
	}

	return height;
}
