#include<stdlib.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include <cstdlib>

#include <time.h>
#include <windows.h>
using namespace std;

int binaria(int arr[], int lbajo, int larriba, int key);



void main() {
	int x = 0, y = 0;

	int vector[15] = { 0,1,2,4,5,6,7,8,9,10 };
	x = binaria(vector, 0, 9, 4);
	y = binaria(vector, 0, 9, 6);
	printf("x= %d, y= %d\n",x,y); 
	


	system("pause>nul");
}

int binaria(int arr[], int lbajo, int larriba, int key) {
	short lcentro = (larriba + lbajo) / 2;
	if (arr[lcentro] == key) {
		return arr[lcentro];
	}
	else if (key < lbajo) {
		binaria(arr, lbajo, lcentro, key);
	}
	else if (key > larriba) {
		binaria(arr, lcentro, larriba, key);
	}
	else { return -1; }

}
