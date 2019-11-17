#include <corecrt_math_defines.h>
#include <math.h>
#include "Primitive.h"

Primitive::Primitive()
{
}

Mesh Primitive::Sphere(int stacks, int slices, float radius, float start, float end)
{
	Vertex* vertex = new Vertex[stacks * slices * 3];
	unsigned int* indexes = new unsigned int[stacks * slices * 6];

	Mesh out;
	for (int i = 0; i < slices; i++)
	{
		for (int j = 0; j < stacks; j++)
		{
			int indice = (i * stacks + j);
			vertex[indice].posX = radius * cos(((double)j / (stacks - 1)) * (M_PI * (end - start)) + M_PI * start - M_PI / 2.0) *
				cos(2.0 * M_PI * (double)i / (slices - 1));
			vertex[indice].posY = radius * sin(((double)j / (stacks - 1)) * (M_PI * (end - start)) + M_PI * start - M_PI / 2.0);
			vertex[indice].posZ = radius * cos(((double)j / (stacks - 1)) * (M_PI * (end - start)) + M_PI * start - M_PI / 2.0) *
				sin(2.0 * M_PI * (double)i / (slices - 1));

			vertex[indice].normX = cos(((double)j / (stacks - 1)) * (M_PI * (end - start)) + M_PI * start - M_PI / 2.0) *
				cos(2.0 * M_PI * (double)i / (slices - 1));
			vertex[indice].normY = sin(((double)j / (stacks - 1)) * (M_PI * (end - start)) + M_PI * start - M_PI / 2.0);
			vertex[indice].normZ = cos(((double)j / (stacks - 1)) * (M_PI * (end - start)) + M_PI * start - M_PI / 2.0) *
				sin(2.0 * M_PI * (double)i / (slices - 1));

			vertex[indice].u = (float)1 * (1 - (float)i / (stacks - 1));
			vertex[indice].v = (float)1 * (1 - (float)j / (slices - 1));
		}
	}

	//ahora la parte mas importante de crear vertices es el algoritmo para unirlos, en este caso sustituiremos
	//a un algoritmo con un un grupo de indices

	int index = 0;
	for (int i = 0; i < slices - 1; i++)
	{
		for (int j = 0; j < stacks - 1; j++)
		{
			indexes[index++] = i * stacks + j;
			indexes[index++] = (i + 1) * stacks + j + 1;
			indexes[index++] = i * stacks + j + 1;

			indexes[index++] = i * stacks + j;
			indexes[index++] = (i + 1) * stacks + j;
			indexes[index++] = (i + 1) * stacks + j + 1;
		}
	}

	//una vez generados los damos a conocer a traves del objeto "salida"
	out.mesh = vertex;
	out.indexes = indexes;

	return out;
}

Mesh Primitive::Plane(int vertexX, int vertexZ, float width, float depth)
{
	//Cargamos la estructura con los espacios de memoria necesarios
	Vertex* vertex = new Vertex[vertexX * vertexZ * 3];
	unsigned int* indexes = new unsigned int[vertexX * vertexZ * 6];

	//es la separacion entre vertices, se le resta 1 para que el lado correcto
	//imagine que el ancho es de 10 y tiene 10 vertices, entonces le daria un deltax
	//de 1, si los vertices van de 0 a 9 entonces la posicion del ultimo vertice
	//seria 9, si le divide entre vertexX -1 le dara 1.1111, y el ultimo vertice sera 10
	float deltax = width / (vertexX - 1);
	float deltaz = depth / (vertexZ - 1);

	//crea los vertices
	for (int z = 0; z < vertexZ; z++)
	{
		for (int x = 0; x < vertexX; x++)
		{
			vertex[z * vertexX + x].posX = (float)x * deltax;
			vertex[z * vertexX + x].posY = 0.0;
			vertex[z * vertexX + x].posZ = (float)z * deltaz;

			//carga las normales con cero
			vertex[z * vertexX + x].normX = 0.0;
			vertex[z * vertexX + x].normY = 0.0;
			vertex[z * vertexX + x].normZ = 0.0;
		}
	}

	//calcula los uv's
	for (int z = 0; z < vertexZ; z++)
	{
		for (int x = 0; x < vertexX; x++)
		{
			vertex[z * vertexX + x].u = (float)x / (vertexX - 1);
			vertex[z * vertexX + x].v = (float)z / (vertexZ - 1);
		}
	}

	Vector3 aux;
	//crea las normales
	for (int z = 0; z < (vertexX - 1); z++)
	{
		for (int x = 0; x < (vertexX - 1); x++)
		{
			aux = GetNormal(&vertex[z * vertexX + x].posX, &vertex[(z + 1) * vertexX + (x + 1)].posX,
				&vertex[z * vertexX + (x + 1)].posX);

			AddNormal(&vertex[z * vertexX + x].normX, &aux.x);
			AddNormal(&vertex[(z + 1) * vertexX + (x + 1)].normX, &aux.x);
			AddNormal(&vertex[z * vertexX + (x + 1)].normX, &aux.x);

			aux = GetNormal(&vertex[z * vertexX + x].posX, &vertex[(z + 1) * vertexX + x].posX,
				&vertex[(z + 1) * vertexX + (x + 1)].posX);

			AddNormal(&vertex[z * vertexX + x].normX, &aux.x);
			AddNormal(&vertex[(z + 1) * vertexX + x].normX, &aux.x);
			AddNormal(&vertex[(z + 1) * vertexX + (x + 1)].normX, &aux.x);
		}
	}

	//Normaliza las normales
	for (int z = 0; z < vertexZ; z++)
	{
		for (int x = 0; x < vertexX; x++)
		{
			Normalize(&vertex[z * vertexX + x].normX);
		}
	}

	//ahora la parte mas importante de crear vertices es el algoritmo para unirlos, en este caso sustituiremos
	//a un algoritmo con un un grupo de indices
	int index = 0;
	for (int i = 0; i < vertexZ - 1; i++)
	{
		for (int j = 0; j < vertexX - 1; j++)
		{
			indexes[index++] = i * vertexZ + j;
			indexes[index++] = (i + 1) * vertexZ + j + 1;
			indexes[index++] = i * vertexZ + j + 1;

			indexes[index++] = i * vertexZ + j;
			indexes[index++] = (i + 1) * vertexZ + j;
			indexes[index++] = (i + 1) * vertexZ + j + 1;
		}
	}

	//generamos un objeto para poder transportar los punteros

	Mesh out;

	out.mesh = vertex;
	out.indexes = indexes;

	return out;
}

Mesh Primitive::Plane(int vertexX, int vertexZ, float width, float depth, unsigned char* height, float tile)
{
	//Cargamos la estructura con los espacios de memoria necesarios
	Vertex* vertex = new Vertex[vertexX * vertexZ * 3];
	unsigned int* indexes = new unsigned int[vertexX * vertexZ * 6];

	//es la separacion entre vertices, se le resta 1 para que el lado correcto
	//imagine que el ancho es de 10 y tiene 10 vertices, entonces le daria un deltax
	//de 1, si los vertices van de 0 a 9 entonces la posicion del ultimo vertice
	//seria 9, si le divide entre vertexX -1 le dara 1.1111, y el ultimo vertice sera 10
	float deltaX = width / (vertexX - 1);
	float deltaZ = depth / (vertexZ - 1);

	//crea los vertices
	for (int z = 0; z < vertexZ; z++)
	{
		for (int x = 0; x < vertexX; x++)
		{
			vertex[z * vertexX + x].posX = (float)x * deltaX - width / 2.0;
			vertex[z * vertexX + x].posY = (float)height[z * vertexX * 4 + x * 4] ;// "/ 10.0" ,"255"
			vertex[z * vertexX + x].posZ = (float)z * deltaZ - depth / 2.0;

			//carga las normales con cero
			vertex[z * vertexX + x].normX = 0.0;
			vertex[z * vertexX + x].normY = 1.0;
			vertex[z * vertexX + x].normZ = 0.0;
		}
	}

	//calcula los uv's
	for (int z = 0; z < vertexZ; z++)
	{
		for (int x = 0; x < vertexX; x++)
		{
			vertex[z * vertexX + x].u = (float)(x * tile) / (vertexX - 1);
			vertex[z * vertexX + x].v = (float)(z * tile) / (vertexZ - 1);
		}
	}

	Vector3 aux;
	//crea las normales
	for (int z = 0; z < (vertexZ - 1); z++)
	{
		for (int x = 0; x < (vertexX - 1); x++)
		{
			aux = GetNormal(&vertex[z * vertexX + x].posX, &vertex[z * vertexX + (x + 1)].posX,
				&vertex[(z + 1) * vertexX + (x + 1)].posX);

			AddNormal(&vertex[z * vertexX + x].normX, &aux.x);
			AddNormal(&vertex[(z + 1) * vertexX + (x + 1)].normX, &aux.x);
			AddNormal(&vertex[z * vertexX + (x + 1)].normX, &aux.x);

			aux = GetNormal(&vertex[z * vertexX + x].posX, &vertex[(z + 1) * vertexX + x + 1].posX,
				&vertex[(z + 1) * vertexX + x].posX);

			AddNormal(&vertex[z * vertexX + x].normX, &aux.x);
			AddNormal(&vertex[(z + 1) * vertexX + x].normX, &aux.x);
			AddNormal(&vertex[(z + 1) * vertexX + (x + 1)].normX, &aux.x);
		}
	}

	//Normaliza las normales
	for (int z = 0; z < vertexZ; z++)
	{
		for (int x = 0; x < vertexX; x++)
		{
			Normalize(&vertex[z * vertexX + x].normX);

		}
	}


	//ahora la parte mas importante de crear vertices es el algoritmo para unirlos, en este caso sustituiremos
	//a un algoritmo con un un grupo de indices
	int index = 0;
	for (int i = 0; i < vertexZ - 1; i++)
	{
		for (int j = 0; j < vertexX - 1; j++)
		{
			indexes[index++] = i * vertexZ + j;
			indexes[index++] = (i + 1) * vertexZ + j + 1;
			indexes[index++] = i * vertexZ + j + 1;


			indexes[index++] = (i + 1) * vertexZ + j;
			indexes[index++] = (i + 1) * vertexZ + j + 1; 
			indexes[index++] = i * vertexZ + j;
		}
	}

	//generamos un objeto para poder transportar los punteros

	Mesh out;

	out.mesh = vertex;
	out.indexes = indexes;

	return out;
}
