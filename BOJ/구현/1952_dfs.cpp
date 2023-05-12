#include <iostream>

using namespace std;

int m,n;

int f(int r, int c) {
	if (r == 1) return 0;
	return f(c, r - 1) + 1;
}

int main() {
	cin >> m >> n;
	cout << f(m,n);
	return 0;
}
