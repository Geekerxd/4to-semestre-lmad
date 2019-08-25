//
// Define la clase LibroCalificaciones con una funcion miembro llamada mostrarMesnaje;
// Crea un objeto LibroCalificaciones y llama a su funci�n mostrarMensaje.
#include <iostream>
using std::cout;// 0
using std::endl;

// Definici�n de la clase LibroCalificaciones
class LibroCalificaciones
{
public:
	// funci�n que muestra un mensaje de bienvenida para el usuario de LibroCalificaciones
	void mostrarMensaje()
	{
		cout << "Bienvenido al Libro de calificaciones! yay" << endl;
	} // fin de la funcion mostrarMensaje
}; // fin de la clase LibroCalificaciones

// la funcion main empieza la ejecuci�n del programa
int main()
{
	LibroCalificaciones miLibroCalificaciones; // crea un objeto LibroCalificaciones
	miLibroCalificaciones.mostrarMensaje(); // llama a la funcion mostrarMensaje del objeto
	system("pause>nul"); 
	return 0; // indica que termin� correctamente
} // fin del main