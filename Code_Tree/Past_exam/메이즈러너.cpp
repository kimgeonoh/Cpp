// 정사각형 만드는 알고리즘 문제점 발견, 모든 경우의 수가 없다
// 

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M, K, ex, ey;
int maze[11][11];
int dx[4] = { -1,1,0,0 }; // 상하 좌우
int dy[4] = { 0,0,-1,1 };

struct Participant {
	int x;
	int y;
	int c;
	int exit;
};

struct Rectangular {
	int size;
	int r;
	int c;
	bool operator<(const Rectangular& down) const {
		if (size != down.size) return size > down.size;
		if (r != down.r) return r > down.r;
		if (c != down.c) return c > down.c;
		return 0;
	}
};

Participant participant[12]; // 1 ~ M
priority_queue<Rectangular> rectangular;

void input() {
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> maze[i][j];
		}
	}
	for (int i = 0; i < M; i++) {
		cin >> participant[i].x >> participant[i].y;
	}
	cin >> ex >> ey;
	maze[ex][ey] = -1;
}

bool move(int x, int y, int* mx, int* my) {
	int short_d = abs(x - ex) + abs(y - ey);
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (nx < 1 || N < nx || ny < 1 || N < ny) continue;
		if (maze[nx][ny] > 0) continue;

		int d = abs(nx - ex) + abs(ny - ey);
		if (d >= short_d) continue;

		*mx = nx;
		*my = ny;

		return 1;
	}
	return 0;
}

void participant_exit(int number) { // 출구와 참가자가 같이 있다면
	if (maze[participant[number].x][participant[number].y] == -1) {
		participant[number].exit = 1;
	}
}

bool simulation_exit() {
	// 모든 참가자가 탈출에 성공한 경우가 아닌 경우
	for (int i = 0; i < M; i++) {
		if (participant[i].exit == 0) return 0;
	}
	// 전원 탈출 성공
	return 1;
}

void simulation() {

	// ex, ey init
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (maze[i][j] == -1) {
				ex = i;
				ey = j;
			}
		}
	}

	// 1. 참가자 이동
	for (int i = 0; i < M; i++) {
		int mx = -1, my = -1;
		if (participant[i].exit == 1) continue; // 탈출한 사람은 예외
		if (move(participant[i].x, participant[i].y, &mx, &my)) { // 움직인 경우
			participant[i].c += 1; // 답 체크
			participant[i].x = mx;
			participant[i].y = my;
		}
		participant_exit(i);
	}

	// 이동한 후 모든 참가자가 탈출했을 경우
	if (simulation_exit()) return;

	// 2. 맵 회전
	// 정사각형 구하기
	rectangular = priority_queue<Rectangular>();
	
	for (int size = 2; size <= N; size++) { // 가장 작은 정사각형부터 탐색
		for (int r = 1; r <= N - size; r++) { // 가장 위에 r 좌표부터 시작
			for (int c = 1; c <= N - size; c++) { // 가장 왼쪽에 c좌표부터 시작
				int r2 = r + size - 1;
				int c2 = c + size - 1;

				// 만약 출구가 해당 정사각형 안에 없다면 스킵합니다.
				if (ex < r || r2 < ex || ey < c || c2 < ey) {
					continue;
				}
				// 한 명 이상의 참가자가 해당 정사각형 안에 있는지 판단합니다.
				bool is_participant_in = false;
				for (int l = 0; l < M; l++) {
					if (r <= participant[l].x && participant[l].x <= r2 && c <= participant[l].y && participant[l].y <= r2) {
						// 출구에 있는 참가자는 제외합니다.
						if (participant[l].exit == 1) {
							continue;
						}
						is_participant_in = true;
					}
				}

				// 만약 한 명 이상의 참가자가 해당 정사각형 안에 있다면
				// sx, sy, sqaure_size 정보를 갱신하고 종료합니다.
				if (is_participant_in) {
					rectangular.push({ size, r, c });	
				}
			}
		}
	}

	Rectangular smallest_rectangular = rectangular.top();
	int size = smallest_rectangular.size;
	int sx = smallest_rectangular.r;
	int sy = smallest_rectangular.c;
	int fx = sx + size - 1;
	int fy = sy + size - 1;

	// (sx,sy) ~ (fx,fy)

	// 정사각형 돌리기
	// 돌릴 때 참가자가 있다면 참가자도 돌려야 한다
	int maze_temp[11][11]{}; // maze -> maze_temp, 90degree

	// maze sx, sy ~ fx, fy -> maze_temp 0 ~ size
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			maze_temp[i + 1][j + 1] = maze[sx + i][sy + j];
		}
	}

	int visit[11]{};
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			// 90도 시계방향 회전
			maze[sx + i][sy + j] = maze_temp[size - j][i + 1];
			// 회전된 벽은 내구도가 감소한다
			if (maze[sx + i][sy + j] > 0) maze[sx + i][sy + j]--;

			// 움직인 것이 참가자라면 참가자의 위치를 갱신해준다
			for (int k = 0; k < M; k++) {

				if (participant[k].exit == 1) continue; // 탈출한 녀석은 위치를 갱신하지 않는다

				int standard_x = participant[k].x - sx + 1;
				int standard_y = participant[k].y - sy + 1;

				if (standard_x != size - j || standard_y != i + 1) continue;
				if (visit[k] == 1) continue;

				visit[k] = 1; // 한번 위치를 바꾼놈은 더이상 이번 턴에서는 위치를 갱신하지 않는다
				participant[k].x = sx + i;
				participant[k].y = sy + j;
			}
		}
	}

}

void output() {
	// 이동 거리 합
	int answer = 0;
	for (int i = 0; i < M; i++) {
		answer += participant[i].c;
	}
	cout << answer << '\n';
	// 출구 좌표
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (maze[i][j] == -1) cout << i << ' ' << j << '\n';
		}
	}
}

int main() {
	//freopen("input.txt", "r", stdin);
	input();

	for (int i = 1; i <= K; i++) {
		simulation();
		if (simulation_exit()) break;
	}
	output();
}
