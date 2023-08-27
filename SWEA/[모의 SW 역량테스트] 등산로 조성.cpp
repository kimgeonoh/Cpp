#include <iostream>
#include <queue>

using namespace std;

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
int arr[9][9];

int T, n, k;
int visit[5][89] = { 0 }; // [높은 봉우리][x*10 + y] = 지났으면 1
int max_len = 0;

void dfs(int now, int now_x, int now_y, int len, int dig) {
    // (1)높은봉우리, (2)현재 y위치, (3)현재 x위치, (4)등산로 길이, (5)팔수 있는지(0또는 1)
    if (max_len < len) {
        max_len = len;
    }
    for (int i = 0; i < 4; i++) {
        int nx = dx[i] + now_x;
        int ny = dy[i] + now_y;
        if (nx < 0 || ny < 0 || n <= nx || n <= ny) continue;
        if (visit[now][nx * 10 + ny] == 1) continue;

        if (dig == 0 && arr[nx][ny] >= arr[now_x][now_y]) {
            int diff_h = arr[nx][ny] - arr[now_x][now_y];
            if (diff_h  <  k) {
                arr[nx][ny] -= diff_h + 1;
                visit[now][nx * 10 + ny] = 1;
                dfs(now, nx, ny, len + 1, 1);
                visit[now][nx * 10 + ny] = 0;
                arr[nx][ny] += diff_h + 1;
            }
        }

        if (arr[nx][ny] >= arr[now_x][now_y]) continue; // 깍지 않고 현재 위치보다 높거나 같으면 못감
        visit[now][nx * 10 + ny] = 1;
        dfs(now, nx, ny, len + 1, dig);
        visit[now][nx * 10 + ny] = 0;
    }
}

int main() {
    cin >> T;
    for (int t = 1; t <= T; t++) {
        int maxh = 0, cnt = 0;
        max_len = 0;

        cin >> n >> k;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> arr[i][j];
                if (maxh < arr[i][j]) {
                    maxh = arr[i][j];
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (arr[i][j] == maxh) {
                    visit[cnt][i * 10 + j] = 1;
                    dfs(cnt, i, j, 0, 0);
                    visit[cnt][i * 10 + j] = 0;
                    cnt += 1;
                }
            }
        }
        cout << "#" << t << " " << max_len + 1 << endl;
    }
}
