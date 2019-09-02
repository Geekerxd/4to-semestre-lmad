//#include <iostream>
////#include <math.h>
//using namespace std;
//
//char infija[12] = {"A-B/(C*D^E)"};
//char postfija[12];
//char pila[10];
//
//void push(int i);
//void pull(int i);
//
//int c = 0;
//int D = 0;
//
////enum operadores {
////	mas,
////	menos= 1;
////	
////	^,
////};
//
//
//void push(int i) {   //mete a la pila
//	pila[c] = infija[i];
//	
//}
//
//void pull(int i) {  //mete a la posfija  ???
//
//}
//
//void main() {
//	//system("color 1A");
//
//	for (int i = 0; i<12; i++) {
//		switch (infija[i]) {
//		case '(':
//			push(i);
//			c++;
//
//			break;
//		case ')':
//
//			//aquo una funcion que siga hasta )
//
//			break;
//		case '+':
//			if (c == 0 || pila[c] == 40 || pila[c] == 42 || pila[c] == 47 || pila[c] == 40) {
//				push(i);
//			}
//			else {
//				if (pila[c] == 45 || pila[c] == 43) {
//					postfija[c] = pila[c];
//					push(i);
//				}
//			}
//			break;
//		case '-':
//			if (c == 0 || pila[c] == 40) {
//				push(i);
//				c++;
//			}
//			else{
//				if (pila[c] == 45 || pila[c] == 43) {
//					postfija[c] = pila[c];
//					push(i);
//				}
//			}
//
//			break;
//	/*	case :
//
//			cout << "h";
//			system("pause>NUL");
//			break;*/
//		case '/':
//			if (c == 0 || pila[c] == 40 || pila[c] == 45 || pila[c] == 43) { //si es mayor igual
//				push(i);
//				c++;
//			}
//			else {
//				if (pila[c] == 45 || pila[c] == 43) {
//					
//					push(i);
//				}
//				else if(pila[c] == 42 || pila[c] == 47|| pila[c] == 94) { //si es menor igual
//					postfija[c] = pila[c];
//					push(i);
//				}
//			}
//			break;
//		case '*':
//
//			break;
//		case '^':
//
//			break;
//		default:
//			
//
//			if (infija[i] >= 48 && infija[i] <= 57 || infija[i] >= 65 && infija[i] <= 90 || infija[i] >= 97 && infija[i] <= 122) {
//			
//				postfija[D] = infija[i];
//				D++;
//
//			}
//          break;
//
//			
//		}
//
//
//		
//	}
//	
//
//	//system("pause>NUL");
//}


#include <iostream>
//#include <math.h>
using namespace std;

char infija[12] = { "A-B/(C*D^E)" };
char postfija[12];
char pila[10];

void push(int);
void pull(int);
void imprimir();

int c = 0;
int d = 0;

void push(int i) {
	pila[c] = infija[i];
	c++;
}

void pull(int c) {
	for (int cc = c - 1; cc >= 0; cc--) {
		postfija[d] = pila[cc];
		d++;
	}
}

void main() {

	for (int i = 0; i < 12; i++) {
		switch (infija[i]) {
		case '(':
			push(i);
			break;

		case ')':
			pull(c);
			break;

		case '+':
			if (c == 0 || pila[c - 1] == 40) {
				push(i);
			}
			else {
				if (pila[c - 1] == 45 || pila[c - 1] == 43 || pila[c - 1] == 42 || pila[c - 1] == 47 || pila[c - 1] == 40 || pila[c - 1] == 94) {
					postfija[d] = pila[c - 1];
					d++;
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
					postfija[d] = pila[c - 1];
					d++;
					push(i);
				}
			}
			break;

		case '/':
			if (c == 0 || pila[c - 1] == 40 || pila[c - 1] == 45 || pila[c - 1] == 43) {
				push(i);
			}
			else if (pila[c - 1] == 42 || pila[c - 1] == 47 || pila[c - 1] == 94) {

				postfija[d] = pila[c - 1];
				d++;
				push(i);
			}
			break;

		case '*':
			if (c == 0 || pila[c - 1] == 40 || pila[c - 1] == 45 || pila[c - 1] == 43) {
				push(i);
			}
			else if (pila[c - 1] == 42 || pila[c - 1] == 47 || pila[c - 1] == 94) {

				postfija[d] = pila[c - 1];
				d++;
				push(i);
			}
			break;

		case '^':
			if (c == 0 || pila[c - 1] == 40 || pila[c - 1] == 45 || pila[c - 1] == 43 || pila[c - 1] == 42 || pila[c - 1] == 47) {
				push(i);
			}
			else if (pila[c - 1] == 94) {
				postfija[d] = pila[c - 1];
				d++;
				push(i);
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

	//_getch();
	//system("pause");
}

void imprimir() {
	for (int i = 0; i < 12; i++) {
		if (postfija[i] != 40) {
			cout << postfija[i];
		}
	}
}