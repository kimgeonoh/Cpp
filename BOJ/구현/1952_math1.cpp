int main() {
	cin >> m >> n;

	while (true) {
		m--;
		cnt++;

		if (m == 0) break;
		
        n--;
		cnt++;
		if (n == 0) break;

		dir *= -1;
	}

	cout << cnt - 1 << endl;
}
