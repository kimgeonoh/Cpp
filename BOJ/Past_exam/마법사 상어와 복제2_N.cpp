// 테케 5,6 번이 틀린다

#include <iostream>
#include <deque>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

int M, S, sharkx, sharky;
int dx[8] = {0, -1,-1,-1,0,1,1,1}; // fish_move 시계방향 순
int dy[8] = {-1,-1,0, 1, 1,1,0,-1};
int dx2[5] = {0,-1, 0, 1, 0 }; // shark_move
int dy2[5] = {0, 0,-1, 0, 1 };
int visit[5][5]; // shark_move 에서 가장 많은 물고기를 먹기 위함
int fishsmell[5][5]; // 냄새의 time 를 갖고있다

deque<int> fish[5][5]; // 방향을 갖고있다
deque<int> fish_move[5][5]; // 이동한 다음의 방향을 갖고있다

struct Shark_move { // 상어의 움직임
	int eat_fish;
	string n;
	bool operator<(const Shark_move& down) const {
		if (eat_fish < down.eat_fish) return 1; // 가장 많이 먹은 순
		if (eat_fish > down.eat_fish) return 0;
		if (n > down.n) return 1; // 사전 순
		if (n < down.n) return 0;
		return 0;
	}
};

priority_queue<Shark_move> number; // 상어가 이동할 방향을 탐색한다. {fish, 111 ~ 444} max heap

void shark_move(int sx, int sy, int eat, string temp) {
	if (temp.size() == 3) {
		number.push({eat, temp});
		return;
	}

	for (int i = 1; i <= 4; i++) {
		int nx = sx + dx2[i];
		int ny = sy + dy2[i];
		int ne = eat;
		
		if (nx < 1 || 4 < nx || ny < 1 || 4 < ny) continue;
		if (visit[nx][ny] == 1) continue;
		
		// 처리
		visit[nx][ny] = 1;
		temp += (char)(i+'0');
		// 먹고
		if (!fish_move[nx][ny].empty()) ne += fish_move[nx][ny].size();
		// 들어가고
		shark_move(nx, ny, ne , temp);
		// 초기화
		temp.pop_back();
		visit[nx][ny] = 0;
	}
}

void shark_move_d(int dir) {

	sharkx = sharkx + dx2[dir];
	sharky = sharky + dy2[dir];
	while (!fish_move[sharkx][sharky].empty()) {
		fish_move[sharkx][sharky].pop_back();
		fishsmell[sharkx][sharky] = 3;
	}
	
}

bool counter_clk_wise(int* nx, int* ny, int* d, int i, int j, int t) {

	if (t == 8) return true; // 이동할 수 없다

	if (*nx < 1 || 4 < *nx || *ny < 1 || 4 < *ny) { // 격자를 벗어났다면
		*d -= 1;
		if (*d == -1) *d = 7;
		*nx = i + dx[*d];
		*ny = j + dy[*d];
		if (counter_clk_wise(nx, ny, d, i, j, t + 1)) return true;
	}
	if (*nx == sharkx && *ny == sharky) { // 상어가 있다면
		*d -= 1;
		if (*d == -1) *d = 7;
		*nx = i + dx[*d];
		*ny = j + dy[*d];
		if(counter_clk_wise(nx, ny, d, i, j, t + 1)) return true;
	}
	if (fishsmell[*nx][*ny] > 0) { // 물고기의 냄새가 있다면
		*d -= 1;
		if (*d == -1) *d = 7;
		*nx = i + dx[*d];
		*ny = j + dy[*d];
		if(counter_clk_wise(nx, ny, d, i, j, t + 1)) return true;
	}

	return false; // 이동할 수 있다
}

void simulation() { // 복사마법을 1 ~ 5 까지 수행한다. 

	// 1. 물고기가 한칸 이동한다.
	
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			while (!fish_move[i][j].empty()) { // fish_move init 
				fish_move[i][j].pop_back();
			}
		}
	}

	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			if (!fish[i][j].empty()) {
				for (int d : fish[i][j]) {
					int origin_d = d;
					int nx = i + dx[d];
					int ny = j + dy[d];
					
					bool flag = true; // 이동할 수 없다 고 가정
					flag = counter_clk_wise(&nx, &ny, &d, i, j, 0);

					// 이동할 수 없다면
					if (flag) fish_move[i][j].push_back(origin_d);

					// 이동할 수 있다면
					else fish_move[nx][ny].push_back(d);
				}
			}
		}
	}
	// 2. 상어가 이동한다 
	number = priority_queue<Shark_move>();
	//while (!number.empty()) number.pop(); // string number init
	for (int i = 0; i < 5; i++) { // visit init
		for (int j = 0; j < 5; j++) {
			visit[i][j] = 0;
		}
	}
	visit[sharkx][sharky] = 1;

	// 시작하기 전에 fish_move에 물고기가 있는경우 (모든 방향에서 움직일 수 없어서 갇힌 fish)
	shark_move(sharkx, sharky, 0, ""); // return string number

	int s_d1 = number.top().n[0] - '0';
	int s_d2 = number.top().n[1] - '0';
	int s_d3 = number.top().n[2] - '0';

	shark_move_d(s_d1);
	shark_move_d(s_d2);
	shark_move_d(s_d3);
	
	// 3. 두번 전 사용한 물고기 냄새가 사라진다.
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			if (fishsmell[i][j] > 0) fishsmell[i][j]--;
		}
	}
	
	// 4. 물고기가 복제되었다
	// fish_move에 있는 놈이 fish 에 들어간다
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			if (!fish_move[i][j].empty()) {
				for (int d : fish_move[i][j]) {
					fish[i][j].push_back(d);
				}
			}
		}
	}
}

void output() { // 모든 물고기의 개수를 파악
	int answer = 0;
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			if (!fish[i][j].empty()) {
				for (int d : fish[i][j]) {
					answer++;
				}
			}
		}
	}
	cout << answer << '\n';
}

int main() {
	//input
	cin >> M >> S;
	for (int i = 0; i < M; i++) {
		int x, y, dir; cin >> x >> y >> dir;
		fish[x][y].push_back({ dir - 1 });
	}
	cin >> sharkx >> sharky;
	// simulation
	for(int i=1; i<=S; i++) simulation();
	// output
	output();
}
