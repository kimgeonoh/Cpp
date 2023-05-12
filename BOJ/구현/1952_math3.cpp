#include <iostream>

using namespace std;

int m,n;
int sum, count;

int main() {
	cin >> m >> n;
	
	sum = m * n;
	
	m--;
	while (1) {
		sum -= n;
		if (sum != 0) {
			count++;
			n--;
		}
		else break;
		
		sum -= m;
		if (sum != 0) {
			count++;
			m--;
		}
		else break;
	}
	cout << count;
}
