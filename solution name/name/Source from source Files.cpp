#include <iostream>
using namespace std;

int factorial(int n) {
	if (n == 0)
		return 1;
	else
		return n * factorial(n - 1);




}

void main() {
	int x, y;
	cin >> x;
	y = factorial(x);
	printf("fact = %d", y);

	system("pause>NUL");



}