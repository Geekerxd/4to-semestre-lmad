#include <iostream>
#include <math.h>
using namespace std;

char infija[12] = {"A-B/(C*D^E)"};
char postfija[12];
char pila[10];

void push(int);
void pull(int);

int c = 0;
int D = 0;

//enum operadores {
//	mas,
//	menos= 1;
//	
//	^,
//};


void push(int i) {
	pila[c] = infija[i];
	c++;
}

void pull(int i) {

}

void main() {
	system("color 1A");

	for (int i = 0; i<12; i++) {
		switch (infija[i]) {
		case '(':
			push(i);
			

			break;
		case ')':

			break;
		case '+':
			if (c == 0 || pila[c] == 40 || pila[c] == 42 || pila[c] == 47 || pila[c] == 40) {
				push(i);
			}
			else {
				if (pila[c] == 45 || pila[c] == 43) {
					postfija[c] = pila[c];
					push(i);
				}
			}
			break;
		case '-':
			if (c == 0 || pila[c] == 40) {
				push(i);
			}
			else{
				if (pila[c] == 45 || pila[c] == 43) {
					postfija[c] = pila[c];
					push(i);
				}
			}

			break;
	/*	case :

			cout << "h";
			system("pause>NUL");
			break;*/
		case '/':
			if (c == 0 || pila[c] == 40) {
				push(i);
			}
			else {
				if (pila[c] == 45 || pila[c] == 43) {
					
					push(i);
				}
				else if(pila[c] == 42 || pila[c] == 47) {
					postfija[c] = pila[c];
					push(i);
				}
			}
			break;
		case '*':

			break;
		case '^':

			break;
		default:
			postfija[D] = infija[i];
			D++;

			break;

			
		}


		
	}
	

	system("pause>NUL");
}