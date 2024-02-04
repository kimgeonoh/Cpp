// 새로운 불면증 치료법1을 bit masking이 아닌 for문으로 푼 풀이입니다.
// 이 풀이는 직관적으로 생각해내기는 쉽지만 효율성면에서는 bit masking보다 떨어집니다.

// https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV18_yw6I9MCFAZN
// 1288
// for

#include <iostream>
#include <string>

using namespace std;

bool visited[10];

int check() {
	int cnt = 0;
	for (int i = 0; i < 10; i++) {
		if (visited[i] == 1) cnt++;
	}
	if (cnt == 10) return true;
	return false;
}

int main() {
	int testcase;
	cin >> testcase;
	int total = (1 << 10) - 1;  // 모든 숫자가 등장했을 때의 값

	for (int i = 1; i <= testcase; i++) {
		int N;
		cin >> N;

		// inital
		for (int i = 0; i < 10; i++) {
			visited[i] = 0;
		}
		int count = 0;
		while (true) {
			string strNum = to_string(N * (++count));  // N*count 값을 문자열로 표현한 것  (예: 5 * 13 = 65 -> "65")
			for (char c : strNum) {
				int num = c - '0';
				visited[num] = true;
			}
			if (check())  // 모든 숫자가 등장했다면, 종료
				break;
		}

		cout << "#" << i << " " << N * count << endl;
	}

	return 0;
}
