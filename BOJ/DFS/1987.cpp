#include <iostream>
#include <algorithm>

#define MAX 20

using namespace std;

int R, C, answer;
char MAP[MAX][MAX];
bool visit[26];

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

void dfs(int x, int y, int cnt) {
	answer = max(answer, cnt);
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (0 <= nx && 0 <= ny && nx < R && ny < C) {
			if (visit[MAP[nx][ny] - 'A'] == false) {
				visit[MAP[nx][ny] - 'A'] = true;
				dfs(nx, ny, cnt + 1);
				visit[MAP[nx][ny] - 'A'] = false;
			}
		}
	}
}

int main(){
	
	cin >> R >> C;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> MAP[i][j];
		}
	}
	
	visit[MAP[0][0] - 'A'] = true;
	dfs(0, 0, 1);
	cout << answer << '\n';
	
	return 0;
}
