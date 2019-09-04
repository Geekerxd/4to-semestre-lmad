/*
#include <iostream>
using std::cout;
using std::endl;

// Definición de la clase LibroCalificaciones
class LibroCalificaciones
{
public:
	// función que muestra un mensaje de bienvenida para el usuario de LibroCalificaciones
	void mostrarMensaje()
	{
		cout << "Bienvenido al Libro de calificaciones! yay" << endl;
	} // fin de la funcion mostrarMensaje
}; // fin de la clase LibroCalificaciones


int main()
{
	LibroCalificaciones miLibroCalificaciones; // crea un objeto LibroCalificaciones
	miLibroCalificaciones.mostrarMensaje();    // llama a la funcion mostrarMensaje del objeto





	system("pause>nul"); 
	return 0; 
} */

#include <iostream>
#include <conio.h>
#include <math.h>
using namespace std;

float cono[10][20][3];
#define X 0
#define Y 1
#define Z 2
#define PI 6.283185
float p1x = 0, p1y = 0;
float p2x = 10, p2y = 10;

void main()
{
	float m, b;
	//calcular m y b
	m = (p2y - p1y) / (p2x - p1x);
	b = p2y - m * p2x;
	//calcular los puntos de la recta
	for (int i = 0; i < 20; i++)
	{
		cono[0][i][X] = i;
		cono[0][i][Y] = m * i + b;
		cono[0][i][Z] = 0;
	}
	//calcular las rectas del cono
	for (int i = 0; i < 20; i++)
		for (int j = 1; j < 10; j++)
		{
			cono[j][i][X] = cono[0][i][X] * cos(j*PI / 10);
			cono[j][i][Y] = cono[0][i][Y];
			cono[j][i][Z] = cono[0][i][X] * sin(j*PI / 10);
		}
	_getch();
}