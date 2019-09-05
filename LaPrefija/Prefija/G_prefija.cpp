
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
char LaPrefija[100];
char InvPrefija[100];

void push(int i);
void imprimir(char *aux);
void change();

int c = 0, d = 0;//POSTfija
int _c = 0;



int tamano;
char ch[100];
//protocolos
void Postfija(string exp);
void PREfija();
void BorrarPilaOpe(char *B);

int main() {


	string expresion;
	cout << "\nIngresa algo:  ";
	getline(cin, expresion); tamano = expresion.length();
	cout << "\nUsted ingreso: " << expresion << "\nDe tamano: " << tamano << endl;


	Postfija(expresion);
    BorrarPilaOpe(postfija);
    cout << "\n\n\n"<< "Postfija: ";
	imprimir(postfija);


	
	PREfija();
	BorrarPilaOpe(InvPrefija);
	cout << endl << "Prefija: ";

	change();
	imprimir(LaPrefija);

	system("pause>NUL");
	return 0;
}
void Postfija(string exp) {//POST 


	strcpy_s(ch, exp.c_str());

	//cout << "Su expresion en char es: " << ch << endl;

	system("pause>nul");

	for (int i = 0; i < tamano; i++) {
		switch (ch[i]) {
		case '(':
			push(i);
			_c += 1;
			break;

		case ')':
			//pull(c);
			_c += 1;
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
void PREfija() {                                               //PRE 
	c = 0; d = 0;//inicializo
	for (int i = tamano; i >= 0; i--) {
		

		switch (ch[i]) {
		case '(':

			while (pila[c - 1] != 41) {
				InvPrefija[d] = pila[c - 1];
				d++;
				c--;
				pila[c] = 0;


			}

			while (c  > 0 && pila[c - 1] == 41) {//Esta bien? while(pila[c - 1] == 41) 
				c--;
				pila[c] = 0;
				if (pila[c - 1] == 41 || pila[c - 1] == 45 || pila[c - 1] == 43 || pila[c - 1] == 42 || pila[c - 1] == 47 || pila[c - 1] == 94) {
					break;
				}
			}
			break;

		case ')':
			push(i);
			break;

		case '+':
			if (c == 0 || pila[c - 1] == '+' || pila[c - 1] == '-' || pila[c - 1] == ')') {
				push(i);
			}
			else if( pila[c - 1] == '*' || pila[c - 1] == '/' || pila[c - 1] == '^') {
					while (c >= 1)// && pila[c - 1] != ')'
					{
						
						if (pila[c - 1] == '+' || pila[c - 1] == '-' || pila[c - 1] == ')') { break; }
						InvPrefija[d] = pila[c - 1];
						c--;
						d++;
						pila[c] = 0;//borrar pila
					}
					push(i);
			}
			break;

		case '-':
			if (c == 0 || pila[c - 1] == '+' || pila[c - 1] == '-'  || pila[c - 1] == ')') {
				push(i);
			}
			else if( pila[c - 1] == '*' || pila[c - 1] == '/' || pila[c - 1] == '^') {
				while (c >= 1 )// && pila[c - 1] != ')'
				{
					
					if (pila[c - 1] == '+' || pila[c - 1] == '-' || pila[c - 1] == ')') { break; }

					InvPrefija[d] = pila[c - 1];
					c--;
					d++;
					pila[c] = 0;//borrar pila
				}
				push(i);
				
			}
			break;

		case '/':
			if (c == 0 ||pila[c - 1] == '+' || pila[c - 1] == '-' || pila[c - 1] == '*' || pila[c - 1] == '/'  || pila[c - 1] == ')') {
				push(i);
			}
			else if (  pila[c - 1] == '^') {

				while (c >= 1 )
				{
					
					if (pila[c - 1] == '+' || pila[c - 1] == '-' || pila[c - 1] == '*' || pila[c - 1] == '/' || pila[c - 1] == ')') { break; }
					InvPrefija[d] = pila[c - 1];
					c--;
					d++;
					pila[c] = 0;//borrar pila
				}
				push(i);
			}
			break;
			
		case '*':
			if (c == 0 || pila[c - 1] == '+' || pila[c - 1] == '-' || pila[c - 1] == '*' || pila[c - 1] == '/' || pila[c - 1] == ')') {
				push(i);
			}
			else if (pila[c - 1] == '^') {

				while (c >= 1)
				{
					
					if (pila[c - 1] == '+' || pila[c - 1] == '-' || pila[c - 1] == '*' || pila[c - 1] == '/' || pila[c - 1] == ')') { break; }
					InvPrefija[d] = pila[c - 1];
					c--;
					d++;
					pila[c] = 0;//borrar pila
				}
				push(i);
			}
			break;

		case '^':
			if (c == 0 || pila[c - 1] == '+' || pila[c - 1] == '-' || pila[c - 1] == '*' || pila[c - 1] == '/' || pila[c - 1] == '^' || pila[c - 1] == ')') {
				push(i);
			}
			else
				cout << "\n\tPaso por aqui\t\n";

			break;

		default:
			if (ch[i] >= 48 && ch[i] <= 57 || ch[i] >= 65 && ch[i] <= 90 || ch[i] >= 97 && ch[i] <= 122) {
				InvPrefija[d] = ch[i];
				d++;
			}
			break;
		}
	}


}
void BorrarPilaOpe(char *B) {
	while (c > 0) {
		B[d] = pila[c - 1];
		c--;
		d++;
		pila[c] = 0;//borra los ultimo de la pila de operadores
	}
}
void change() { 
	int z = tamano - _c;
	for (int i = 0; i < tamano - _c; i++) {
		LaPrefija[i] = InvPrefija[z - 1];
	
		z--;
	}

}

void push(int i) {
	pila[c] = ch[i]; //i
	c++;
}

void imprimir(char *aux) {
	
	for (int i = 0; i < tamano - _c; i++) {
		if (aux[i] != 40 && aux[i] != 41) {
			
			cout << aux[i];
		}
		else _c += 1; 

	}
	cout << "   , (: " << _c<<endl;
}