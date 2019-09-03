#include <iostream>
#include <math.h>
#include <cstring>
#include <string>
using namespace std;

char infija[12] = {"A-B/(C*D^E)"};
string postfija;
string pila;
char gg[];
void push(int i, string exp);
void pull(int c);
void imprimir();
int c = 0;
int d = 0;

int tamano;

//protocolos
void Postfija(string exp);

int main() {

	
	string expresion;
	cout << "\nIngresa algo:  ";
	getline(cin, expresion);
	cout << "\nUsted ingreso: " << expresion << " de tamaño: " << expresion.length()<<endl; 
	tamano = expresion.length();


	Postfija(expresion);

	system("pause>NUL");
	return 0;
}
void Postfija(string exp) {
	postfija.assign(exp, d,d+1);
	cout << postfija;
	d++;
	postfija.assign(exp, d, d + 1);
	cout << postfija;
	d++;
	postfija.assign(exp, d, d + 1);
	cout << postfija;
	d++;
	postfija.assign(exp, d, d + 1);
	cout << postfija;
	d++;

	system("pause>nul");
	for (int i = 0; i < tamano; i++) {
		switch (exp[i]) {
		case '(':
			push(i, exp);
			break;

		case ')':
			pull(c);
			break;

		case '+':
			if (c == 0 || pila[c - 1] == 40) {
				push(i,exp);
			}
			else {
				if (pila[c - 1] == 45 || pila[c - 1] == 43 || pila[c - 1] == 42 || pila[c - 1] == 47 || pila[c - 1] == 40 || pila[c - 1] == 94) {
					postfija[d] = pila[c - 1];
					d++;
					push(i, exp);
				}
			}
			break;

		case '-':
			if (c == 0 || pila[c - 1] == 40) {
				push(i, exp);
			}
			else {
				if (pila[c - 1] == 45 || pila[c - 1] == 43 || pila[c - 1] == 42 || pila[c - 1] == 47 || pila[c - 1] == 94) {
					postfija[d] = pila[c - 1];
					d++;
					push(i, exp);
				}
			}
			break;

		case '/':
			if (c == 0 || pila[c - 1] == 40 || pila[c - 1] == 45 || pila[c - 1] == 43) {
				push(i, exp);
			}
			else if (pila[c - 1] == 42 || pila[c - 1] == 47 || pila[c - 1] == 94) {

				postfija[d] = pila[c - 1];
				d++;
				push(i, exp);
			}
			break;

		case '*':
			if (c == 0 || pila[c - 1] == 40 || pila[c - 1] == 45 || pila[c - 1] == 43) {
				push(i, exp);
			}
			else if (pila[c - 1] == 42 || pila[c - 1] == 47 || pila[c - 1] == 94) {

				postfija[d] = pila[c - 1];
				d++;
				push(i, exp);
			}
			break;

		case '^':
			if (c == 0 || pila[c - 1] == 40 || pila[c - 1] == 45 || pila[c - 1] == 43 || pila[c - 1] == 42 || pila[c - 1] == 47) {
				push(i, exp);
			}
			else if (pila[c - 1] == 94) {
				postfija[d] = pila[c - 1];
				d++;
				push(i, exp);
			}
			break;

		default:
			if (infija[i] >= 48 && infija[i] <= 57 || infija[i] >= 65 && infija[i] <= 90 || infija[i] >= 97 && infija[i] <= 122) {
				postfija[d] = infija[i];
				d++;
			}
			break;
		}
	}

	imprimir();


}

void push(int i, string exp) {
	pila[c] = exp[i];
	c++;
}

void pull(int c) {
	for (int cc = c - 1; cc >= 0; cc--) {
		postfija[d] = pila[cc];
		d++;
	}
}

void imprimir() {
	cout << endl;
	for (int i = 0; i < 12; i++) {
		if (postfija[i] != 40) {
			cout << postfija[i];
		}
	}
}