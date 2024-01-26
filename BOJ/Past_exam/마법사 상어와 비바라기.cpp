#include <iostream>
#include <vector>

using namespace std;

int N, M, t = 1;
int arr[51][51], cloud_visit[51][51];
int dx[8] = { 0, -1,-1,-1,0,1,1, 1 }; // cloud_move
int dy[8] = { -1,-1,0,  1,1,1,0,-1 };
int dx2[4] = {-1, -1, 1,  1 }; // water_copy
int dy2[4] = {-1, 1,  1, -1 };

struct Cloud {
	int d;
	int s;
};

struct Cordination {
	int x;
	int y;
};

vector<Cloud> cloud_instruction;
vector<Cordination> cloud;
vector<Cordination> cloud_move;

void input() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
		}
	}
	for (int i = 0; i < M; i++) {
		int d, s; cin >> d >> s;
		cloud_instruction.push_back({ d - 1,s }); // d: 1 ~ 8, => 0 ~ 7
	}
}

void init() {
	// cloud_visit
	for (int i = 0; i < 51; i++) {
		for (int j = 0; j < 51; j++) {
			cloud_visit[i][j] = 0;
		}
	}
	// cloud_move
	cloud_move = vector<Cordination>();
}

void simulation(Cloud instruction) {
	
	init();
	// 1. 모든 구름이 d 방향으로 s칸 이동한다
	
	if (t == 1) {
		for (int i = 0; i <= 1; i++) {
			cloud.push_back({ N, i + 1 });
			cloud.push_back({ N - 1, i + 1 });
		}
	}
	t++;

	for (Cordination cordination : cloud) {
		int nowx = cordination.x;
		int nowy = cordination.y;
		int rep = instruction.s;
		int dir = instruction.d;

		int nx = nowx;
		int ny = nowy;
		for (int i = 0; i < rep; i++) {
			nx += dx[dir];
			ny += dy[dir];

			if (N < nx) nx = nx % N;
			if (nx == 0) nx = N;
			if (N < ny) ny = ny % N;
			if (ny == 0) ny = N;
		}
		// 2. 각 구름에서 비가 내려 구름이 있는 칸에 물의 양이 1 증가한다
		arr[nx][ny] += 1;
		// 3. 구름이 사라진다.
		cloud_visit[nx][ny] = 1;
		cloud_move.push_back({ nx,ny });
	}

	cloud = vector<Cordination>();

	// 4. 2에서 물이 증가한 칸에서 물복사 마법을 시작한다.
	//    대각선 방향으로 1인 칸에 물이 있는 바구니의 수 만큼 증가한다.
	//    단, 경계를 넘어가선 안된다.

	for (Cordination cordination : cloud_move) {
		int nowx = cordination.x;
		int nowy = cordination.y;
		int argument = 0;
		for (int i = 0; i < 4; i++) {
			int nx = nowx + dx2[i];
			int ny = nowy + dy2[i];
			if (nx < 1 || N < nx || ny < 1 || N < ny) continue;
			if (arr[nx][ny] == 0) continue;
			argument += 1;
		}
		arr[nowx][nowy] += argument;
	}

	// 5. arr에서 물의 양이 2 이상인 칸에 물의 양이 2 줄어든다. 그리고 구름이 생긴다 
	//    단, 3에서 구름이 사라진 칸이 아니어야 한다.
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (cloud_visit[i][j] == 1) continue;
			if (arr[i][j] >= 2) {
				arr[i][j] -= 2;
				cloud.push_back({ i,j });
			}
		}
	}

}

void output() { // arr 에 들어있는 모든 물의 양 합 출력
	int answer = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			answer += arr[i][j];
		}
	}
	cout << answer << '\n';
}


int main() {
	input();
	for (Cloud v : cloud_instruction) simulation(v);
	output();
}
