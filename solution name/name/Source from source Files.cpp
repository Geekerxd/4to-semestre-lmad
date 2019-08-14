#include <iostream>
using namespace std;

float serie(int n) {
	if (n == 0) 
	return 0;

	else if (n % 2 == 0) 
		return serie(n - 1) - (1 / n);
	
	else 
		return serie(n - 1) + (1 / n);
	

}

void main() {
	float x=0, y=0;
	cout << "insterte n: ";
	cin >> x;
	serie(x);
	y = serie(x);
	//printf("\nTotal de la suma de la serie = %f", y);
	cout << "\nSeria=  "<<y;
	system("pause>NUL");



}