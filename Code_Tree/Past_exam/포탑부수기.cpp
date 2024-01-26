#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int N, M, K;
int arr[11][11], px[11][11], py[11][11], visit[11][11];  // 1 ~ N, 1 ~ M
int time_recent_attack[11][11]{};
int dx[4] = { 0, 1, 0, -1 };                             // 우, 하, 좌, 상
int dy[4] = { 1, 0, -1, 0 };
int dx2[8] = { -1,-1,0,1,1,1,0,-1 };                     // 상, 시계방향
int dy2[8] = { 0,1,1,1,0,-1,-1,-1 };

void input() {
	cin >> N >> M >> K; // N x M 격자, K 번 반복
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> arr[i][j];
		}
	}
}

struct Attack { // 가장 약한 녀석
	int x;
	int y;
	int power;
	int recent_attack;
	bool operator<(const Attack& down) const {
		if (power != down.power) return power > down.power;
		if (recent_attack != down.recent_attack) return recent_attack < down.recent_attack;
		if ((x + y) != (down.x + down.y)) return (x + y) < (down.x + down.y);
		if (y != down.y) return (y < down.y);
		return 0;
	}
};

struct Victim { // 가장 강한 녀석
	int x;
	int y;
	int power;
	int recent_attack;
	bool operator<(const Victim& down) const {
		if (power != down.power) return power < down.power;
		if (recent_attack != down.recent_attack) return recent_attack > down.recent_attack;
		if ((x + y) != (down.x + down.y)) return (x + y) > (down.x + down.y);
		if (y != down.y) return (y > down.y);
		return 0;
	}
};

struct Cordination { // bfs
	int x;
	int y;
};

priority_queue<Attack> attack;
priority_queue<Victim> victim;

bool bfs(int sx, int sy, int tx, int ty) {
	queue<Cordination> q;
	q.push({ sx,sy });
	px[sx][sy] = sx; // 시작지점
	py[sx][sy] = sy;
	while (!q.empty()) {
		Cordination now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = now.x + dx[i];
			int ny = now.y + dy[i];
			if (nx < 1) nx = N;
			if (N < nx) nx = 1;
			if (ny < 1) ny = M;
			if (M < ny) ny = 1;

			if (arr[nx][ny] == 0) continue; // 부서진 포탑
			if (px[nx][ny] > 0) continue; // 한번 방문했던곳
			if (py[nx][ny] > 0) continue;

			px[nx][ny] = now.x; // parent cordination path record
			py[nx][ny] = now.y;

			if (nx == tx && ny == ty) return 1; // 경로를 찾았다

			q.push({ nx,ny });
		}
	}

	return 0; // 경로가 없다
}

void init() {
	// attack, victim
	attack = priority_queue<Attack>();
	victim = priority_queue<Victim>();
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (arr[i][j] > 0) {
				attack.push({ i, j, arr[i][j], time_recent_attack[i][j] });
				victim.push({ i, j, arr[i][j], time_recent_attack[i][j] });
			}
			// parent, visit
			px[i][j] = 0;
			py[i][j] = 0;
			visit[i][j] = 0;
		}
	}
}

void simulation(int try_simulation) {
	// init
	init(); // arr 을 이용, arr 은 항상 최신화가 필요

	// 1. 공격자 선정
	Attack weak = attack.top();
	arr[weak.x][weak.y] += (N + M);
	visit[weak.x][weak.y] = 1; // 공격에 가담된 사람들 기록
	time_recent_attack[weak.x][weak.y] = try_simulation; // 공격한 시간 기록 
	// 2. 공격자의 공격
	Victim strong = victim.top();
	visit[strong.x][strong.y] = 1;
	// 최단 경로 찾기
	// 가능하다면, 레이저 공격
	if (bfs(weak.x, weak.y, strong.x, strong.y)) {
		// victim
		if (arr[strong.x][strong.y] <= arr[weak.x][weak.y]) arr[strong.x][strong.y] = 0;
		else arr[strong.x][strong.y] -= arr[weak.x][weak.y];
		// path
		int pathx = px[strong.x][strong.y];
		int pathy = py[strong.x][strong.y];
		while (1) {
			if (weak.x == pathx && weak.y == pathy) break;

			if (arr[pathx][pathy] <= arr[weak.x][weak.y] / 2) arr[pathx][pathy] = 0;
			else arr[pathx][pathy] -= arr[weak.x][weak.y] / 2;
			visit[pathx][pathy] = 1;
			
			int temp_pathx = pathx;  // pathx 가 비뀌므로 pathy 를 할당할 때 문제 방지
			pathx = px[pathx][pathy];
			pathy = py[temp_pathx][pathy];
		}
	}
	// 불가능하다면, 포탄 공격
	else {
		// victim
		if (arr[strong.x][strong.y] <= arr[weak.x][weak.y]) arr[strong.x][strong.y] = 0;
		else arr[strong.x][strong.y] -= arr[weak.x][weak.y];
		// around
		for (int i = 0; i < 8; i++) {
			int nx = strong.x + dx2[i];
			int ny = strong.y + dy2[i];
			
			if (nx < 1) nx = N;
			if (N < nx) nx = 1;
			if (ny < 1) ny = M;
			if (M < ny) ny = 1;

			if (nx == weak.x && ny == weak.y) continue;
			if (arr[nx][ny] == 0) continue;

			if (arr[nx][ny] <= arr[weak.x][weak.y] / 2) arr[nx][ny] = 0;
			else arr[nx][ny] -= arr[weak.x][weak.y] / 2;
			visit[nx][ny] = 1;
		}
	}

	// 3. 포탑 부서짐

	// 4. 포탑 정비
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (visit[i][j] == 1) continue;
			if (arr[i][j] == 0) continue;
			arr[i][j] += 1;
		}
	}

}

bool simulation_exit() {
	int live_cnt = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (arr[i][j] > 0) live_cnt++;
		}
	}
	if (live_cnt == 1) return true;
	return false;
}

void output() {
	// 가장 강한 포탑의 공격력 출력 => 2. 공격자 선정
	priority_queue<Victim> answer;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (arr[i][j] > 0) answer.push({ i, j, arr[i][j], time_recent_attack[i][j] });
		}
	}
	cout << answer.top().power;
}

int main() {
	input();
	for (int i = 1; i <= K; i++) {
		if (simulation_exit()) break; // 부서지지 않은 포탑이 1개라면 시뮬레이션을 중지한다.
		simulation(i);
	}
	output();
}
