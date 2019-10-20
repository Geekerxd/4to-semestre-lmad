#include<stdlib.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include <cstdlib>

#include <time.h>
#include <windows.h>
using namespace std;
int resp = 0, a, b,usu, count1 = 0, count2 = 0;



void main() {
	printf("\tSi quieres salir ingresa <0\n"); 
	retro:

	while (usu>= 0) {
		srand(time(NULL));
		
		a = rand() % 8 + 3;
		b = rand() % 8 + 3;

		printf("%d * %d= ",a,b);	cin >> usu;
		
		resp = a * b;

		while (1) {
			int z = 0;
			//int to char para validacion
			cout << endl;
			for (int i = 0; i < 250; i++) {
				//system("cls"); if (i%10==0) { Sleep(0.01);
				//} system("cls");
				/*if (i % 20 == 0) {
					system("cls");
					cout << i << endl; Sleep(0.5);
				}*/
				int j = 0;

				if (i < 126) {
					for (j; j <= i; j++)
						cout << "_";
				}
				else {
					for (int k = 0; k <= i - z; k++)
					{
						cout << "_";
					}
					z = z + 2;
				}

				cout << "/";
				cout << endl;


			}

			Sleep(10);
		}
		cout << endl;
		if (resp == usu)
		{
			
			printf("correcto\n"); count1++;
		}
		else
		{
			if (usu <0) break;
			printf("incorrecto. es: %d\n", resp); count2++;
		}



	}
	printf("\n\tObtubiste: %d aciertos y %d fallas.\n", count1, count2);
	
	printf("\n\tSeguir jugando?\n\t 1.-Si\n\t 0.-No\n\t", usu);
	
	cin >> usu;
	if (usu == 1) {
		system("cls");
		count1 = 0;
		count2 = 0;
		goto retro;

	}
	//system("pause>nul");
}


/*
namespace uno{
	//
typedef struct nodo {
	int valor;
	struct nodo *siguiente;
} tipoNodo;
typedef tipoNodo *pNodo;
typedef tipoNodo *Pila;
void Push(Pila *l, int v);
int Pop(Pila *l);int main() {
	Pila pila = NULL;
	Push(&pila, 20);
	Push(&pila, 10);
	printf("%d, ", Pop(&pila)); 
	Push(&pila, 40);
	Push(&pila, 30);            
	printf("%d, ", Pop(&pila)); 
	printf("%d, ", Pop(&pila)); 
	Push(&pila, 90);            
	printf("%d, ", Pop(&pila)); 
	printf("%d\n", Pop(&pila)); 
	system("pause>nul");
	return 0;
}void Push(Pila *pila, int v) {
	pNodo nuevo;
	nuevo = (pNodo)malloc(sizeof(tipoNodo));
	nuevo->valor = v;
	nuevo->siguiente = *pila;
	*pila = nuevo;
}

int Pop(Pila *pila) {
	pNodo nodo;
	int v;
	nodo = *pila;
	if (!nodo) return 0;
	*pila = nodo->siguiente;
	v = nodo->valor;
	free(nodo);
	return v;
}}
namespace dos{
	//

	void funcion1(char **p1) {
		*p1 = (int*)malloc(sizeof(int));
		strcpy(*p1, "Hola mundo\n");
	}
	void funcion2() {
		char *p2 = NULL;
		funcion1(&p2); // Advertir el & delante de p2 
		printf("%s\n", p2);
	}
	int main() {
		funcion2();
		return 0;
	}

}
*/