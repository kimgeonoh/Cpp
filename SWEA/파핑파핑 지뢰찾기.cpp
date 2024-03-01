// https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5LwsHaD1MDFAXc

// 최소 클릭으로 답을 구해야 하므로
// 0 을 클릭하여 모든 숫자를 밝히는 것이 빠르다

#include <iostream>
#include <queue> 
#include <vector>

using namespace std;

int map[300][300];
int ans, N;
const int dr[] = { -1, 1, 0, 0, -1, -1, 1, 1 };
const int dc[] = { 0, 0, -1, 1, 1, -1, -1, 1 };

bool isZero(int r, int c) {
    for (int i = 0; i < 8; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (nr < 0 || nc < 0 || nr >= N || nc >= N) continue;
        if (map[nr][nc] == -2) return false;
    }
    return true;
}

void click(int r, int c) {
    queue<pair<int, int>> q;
    q.push({ r, c });
    map[r][c] = 0;
    while (!q.empty()) {
        pair<int, int> curr = q.front();
        q.pop();
        map[curr.first][curr.second] = 0;
        for (int i = 0; i < 8; i++) {
            int nr = curr.first + dr[i];
            int nc = curr.second + dc[i];
            if (nr < 0 || nc < 0 || nr >= N || nc >= N || map[nr][nc] != -1) continue;
            if (isZero(nr, nc)) q.push({ nr, nc });
            map[nr][nc] = 0;
        }
    }
}

void solve() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (map[i][j] != -1) continue;
            if (isZero(i, j)) { // 주변에 지뢰가 없는가?
                click(i, j); // 클릭
                ans++; // 클릭 개수 증가
            }
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (map[i][j] == -1) ans++; // 밝혀지지않은 칸 증가
        }
    }
}

int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        cin >> N;
        ans = 0;
        for (int i = 0; i < N; i++) {
            string str;
            cin >> str;
            for (int j = 0; j < N; j++) {
                if (str[j] == '.') map[i][j] = -1; // 빈칸
                else map[i][j] = -2; // 지뢰
            }
        }
        solve();
        cout << "#" << tc << " " << ans << "\n";
    }

    return 0;
}
