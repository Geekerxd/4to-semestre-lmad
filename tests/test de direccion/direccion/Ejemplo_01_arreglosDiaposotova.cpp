/*
•Desarrollar un programa que genere un arreglo de
tamaño “n” en forma dinámica con la instrucción
new.

• El valor de “n”, lo proporciona el usuario.

• Y ponerle a cada elemento del arreglo un entero
iniciando en 10 e incrementándose de 10 en 10.

• Recordar utilizar el delete para desasignar el
espacio utilizado de memoria.*/

/*


¡¡¡¡¡¡¡¡¡¡¡     Aviso     !!!!!!!!!!!!!!
¡¡¡¡¡¡¡¡¡¡¡  Este es otro !!!!!!!!!!!!!!

*/
#include <iostream>
#include <conio.h>
using namespace std;

void main() {
	int x;
	cout << "¿Cuantas variables enteras requiere?: ";
	cin >> x;
	int **Alfa = new int *[x];
	for (int k = 0; k < x; k++)
	{
		int *w = new int;
		cout << "valor " << k << ": ";
		cin >> *w;
		Alfa[k] = w;

	}
	cout << endl;
    for (int k = 0; k < x; k++)
	{
		cout << "valor " << k << ": " << **Alfa << endl;
		delete *Alfa;
		*Alfa++;
	}

	try {
		*Alfa -= x;
		throw "\n\t\aSorry error bro";


		delete[] * Alfa;

	}
	catch (const char *msm) {
		cout << msm<<endl;
	}

  system("Pause>nul");
}
class nodo {
public:
	int dato;
	nodo *siguiente;
};