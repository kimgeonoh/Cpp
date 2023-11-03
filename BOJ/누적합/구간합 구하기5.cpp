#include <iostream>

using namespace std;

int N, M;
int arr[1025][1025]; // 1 ~ N, 1 ~ N

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M;

	for (int i = 1; i <= N; i++) { // 4방향에 대해 저장
		for (int j = 1; j <= N; j++) {
			int input; cin >> input;

			if (i == 1 && j == 1) { // 원점
				arr[i][j] = input;
			}
			else if (i == 1) { // 벽에 한 부분이 맞닿아 있는 경우
				arr[i][j] = input + arr[i][j - 1];
			}
			else if (j == 1) { // 벽에 한 부분이 맞닿아 있는 경우
				arr[i][j] = input + arr[i - 1][j];
			}
			else {
				arr[i][j] = input + arr[i][j - 1] + arr[i - 1][j] - arr[i - 1][j - 1];
			}
		}
	}

	for (int i = 0; i < M; i++) {
		int answer = 0;
		int sx, sy, tx, ty; cin >> sx >> sy >> tx >> ty;
		// 4번 계산으로 모든 케이스를 커버할 수 있다.
		if (sx == 1 && sy == 1) { // 원점에서 시작하는 경우
			answer = arr[tx][ty];
		}
		else if (sx == 1) {
			answer = arr[tx][ty] - arr[tx][sy - 1];
		}
		else if (sy == 1) {
			answer = arr[tx][ty] - arr[sx - 1][ty];
		}
		else {
			answer = arr[tx][ty] - arr[sx - 1][ty] - arr[tx][sy - 1] + arr[sx - 1][sy - 1];
		}

		cout << answer << '\n';
	}
}
