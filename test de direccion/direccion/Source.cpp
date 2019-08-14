#include <iostream>
using namespace std;

int BuscaBinario(int a[], int m, int n, int x);
void main() {
	/*
	int datos[] = { 1,2,3,4,5,6,7,8,9 };
	int *pd=datos;

	for (int i = 0; i < 9; i++) {
		cout << *pd++<<"\n";


	}*/

	int r;
	int arreglo[6] = {2, 5, 24, 36, 38, 50};

	r=BuscaBinario(arreglo,1,6,6);

	cout <<r ;
	system("pause>nul");
}


int BuscaBinario(int a[], int m, int n, int x) {
	int medio;
	if (n <= m)
		return -1;
	medio = m + (n - m) / 2;
	if (a[medio] == x)
		return medio;
	else
		if (a[medio] < x)
			return BuscaBinario(a, medio + 1, n, x);
	return BuscaBinario(a, m, medio + 1, x);




}