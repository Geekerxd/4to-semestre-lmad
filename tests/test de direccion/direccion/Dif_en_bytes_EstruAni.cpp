/*#include <iostream>
#include <conio.h>
struct dat_per {
	char pri_nombre[30];
	char seg_nombre[30];
	char pri_apelli[30];
	char seg_apelli[30];
};
struct datos {
	dat_per nombre;
	char telefono[12];
	char direccion[30];
};
datos amigo[3];
void main()
{
	datos *punt1;
	datos *punt2;
	datos *punt3;
	punt1 = &amigo[0];
	punt2 = &amigo[1];
	punt3 = &amigo[2];
	std::cout << "punt1: " << punt1 << std::endl;
	std::cout << "punt2: " << punt2 << std::endl;
	std::cout << "punt3: " << punt3 << std::endl;
	_getch();
}
*/

/*
#include <iostream>
#include <conio.h>
struct dato {
	char nombre[30];
	char apellpat[30];
	char apellmat[30];
	char tel[20];
	char email[30];
	dato *direcc;
};
dato *punt1, *punt2, *punt3;
void main()
{
	dato amigo1, amigo2, amigo3;
	punt1 = &amigo1;
	punt2 = &amigo2;
	punt3 = &amigo3;
	//amigo1.direcc = punt1;

		std::cout << "punt1: " << punt1 << std::endl;
		std::cout << "punt2: " << punt2 << std::endl;
		std::cout << "punt3: " << punt3 << std::endl;

		//diference 152 // ¿acaso *direcc guarda 12 bytes?
	_getch();
}*/#include <iostream>
#include <conio.h>
using namespace std;
/*
struct dato {
	dato *dir1;
	char nombre[30];
	char apellpat[30];
	char apellmat[30];
	char tel[20];
	char email[30];
	dato *dir2;
};
dato *punt1, *punt2;
void main()
{
	dato amigo1;
	dato amigo2;
	punt1 = &amigo1;
	punt2 = &amigo2;
	//amigo1.dir1 = punt1;
	//amigo1.dir2 = punt2;

	std::cout << "punt1: " << punt1 << std::endl;
	std::cout << "punt2: " << punt2 << std::endl;
	//156
	_getch();
}*/class Pareja {
	int a, b;
public:
	void setA(int n) { a = n; }
	void setB(int n) { b = n; }
	int getA() { return a; }
	int getB() { return b; }
	void mostrar() {
		cout << "a = " << a << "; b = " << b << endl;
	}
} p1;int main()
{
	p1.setA(100);
	p1.setB(200);
	p1.mostrar();

	_getch();
	return 0;
}