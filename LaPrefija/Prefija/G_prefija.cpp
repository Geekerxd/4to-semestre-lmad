
#include <iostream>
#include <math.h>
#include <cstring>
#include <string>
#include <string.h>
#include <stdio.h>
using namespace std;

char infija[12] = { "A-B/(C*D^E)" };
char postfija[100];
char pila[100];


void push(int i);
void pull(int c);
void imprimir();

int c = 0;
int d = 0;
int _c = 0;

int tamano;
char ch[100];
//protocolos
void Postfija(string exp);
void intercambiar(int i);

int main() {


	string expresion;
	cout << "\nIngresa algo:  ";
	getline(cin, expresion); tamano = expresion.length();
	cout << "\nUsted ingreso: " << expresion << " de tamaño: " << tamano << endl;



	Postfija(expresion);



	while (c > 0) {
		postfija[d] = pila[c - 1];
	c--;
	d++;
	pila[c ] = 0;//borra el ultimo de la pila de operadores
}


	
	
	imprimir();

	system("pause>NUL");
	return 0;
}
void Postfija(string exp) {


	strcpy_s(ch, exp.c_str());

	//cout << "Su expresion en char es: " << ch << endl;

	system("pause>nul");

	for (int i = 0; i < tamano; i++) {
		switch (ch[i]) {
		case '(':
			push(i);
			break;

		case ')':
			//pull(c);

			while(pila[c-1]!=40){
				postfija[d] = pila[c-1];
				d++;
				c--;
				pila[c] = 0;

				
			}
			
			while (c-1 > 0) {//Esta bien?
				c--;
				pila[c] = 0;
				if (pila[c - 1] == 40|| pila[c - 1] == 45 || pila[c - 1] == 43 || pila[c - 1] == 42 || pila[c - 1] == 47 || pila[c - 1] == 94) {
						break;
				}
			}
			break;

		case '+':
			if (c == 0 || pila[c - 1] == 40) {
				push(i);
			}
			else {
				if (pila[c - 1] == 45 || pila[c - 1] == 43 || pila[c - 1] == 42 || pila[c - 1] == 47 || pila[c - 1] == 40 || pila[c - 1] == 94) {
					while (c >= 1 || pila[c - 1] == 40)
					{
						if (pila[c - 1] == 40 || c == 0) { break; }
						postfija[d] = pila[c - 1];
						c--;
						d++;
						pila[c] = 0;//borrar pila
					}
					push(i);


				}
			}
			break;

		case '-':
			if (c == 0 || pila[c - 1] == 40) {
				push(i);
			}
			else {
				if (pila[c - 1] == 45 || pila[c - 1] == 43 || pila[c - 1] == 42 || pila[c - 1] == 47 || pila[c - 1] == 94) {
					while (c >= 1 || pila[c - 1] == 40)
					{
						if (pila[c - 1] == 40 || c == 0) { break; }
						postfija[d] = pila[c - 1];
						c--;
						d++;
						pila[c] = 0;//borrar pila
					}
					push(i);
				}
			}
			break;

		case '/':
			if (c == 0 || pila[c - 1] == 40 || pila[c - 1] == 45 || pila[c - 1] == 43) {
				push(i);
			}
			else if (pila[c - 1] == 42 || pila[c - 1] == 47 || pila[c - 1] == 94) {

				while (c >= 1 || pila[c - 1] == 40)
				{
					if (pila[c - 1] == 40 || c == 0) { break; }
					postfija[d] = pila[c - 1];
					c--;
					d++;
					pila[c] = 0;//borrar pila
				}
				push(i);
			}
			break;
			//***->
		case '*':
			if (c == 0 || pila[c - 1] == 40 || pila[c - 1] == 45 || pila[c - 1] == 43) {
				push(i);
			}
			else if (pila[c - 1] == 42 || pila[c - 1] == 47 || pila[c - 1] == 94) {

				while (c >= 1 || pila[c - 1] == 40)
				{
					if (pila[c - 1] == 40 || c == 0) { break; }
					postfija[d] = pila[c - 1];
					c--;
					d++;
					pila[c] = 0;//borrar pila
				}
				push(i);
			}
			break;

		case '^':
			if (c == 0 || pila[c - 1] == 40 || pila[c - 1] == 45 || pila[c - 1] == 43 || pila[c - 1] == 42 || pila[c - 1] == 47) {
				push(i);//bien
			}
			else if (pila[c - 1] == 94) {
				while (c >= 1 || pila[c - 1] == 40)
				{
					if (pila[c - 1] == 40 || c == 0) { break; }
					postfija[d] = pila[c - 1];
					c--;
					d++;
					pila[c] = 0;//borrar pila
				}
				push(i);
			}
			break;

		default:
			if (ch[i] >= 48 && ch[i] <= 57 || ch[i] >= 65 && ch[i] <= 90 || ch[i] >= 97 && ch[i] <= 122) {
				postfija[d] = ch[i];
				d++;
			}
			break;
		}
	}




}
void intercambiar(int i) {

	while (c >= 1 || pila[c - 1] == 40)
	{
		postfija[d] = pila[c - 1];
		c--;
		d++;
		pila[c] = 0;//borrar pila
	}
	push(i);

}

void push(int i) {
	pila[c] = ch[i]; //i
	c++;
}

void pull(int c) {
	
}

void imprimir() {
	cout <<endl<<"postfija: ";
	for (int i = 0; i < tamano; i++) {
		if (postfija[i] != 40) {
			
			cout << postfija[i];
		}
		else _c += 1; 
	}
	cout << " , (: " << _c<<endl;
}