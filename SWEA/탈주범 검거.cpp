#include<iostream>
#include<queue>
#include<cstring>
using namespace std;


/*
1
5 6 2 2 6
3 0 0 0 0 3
2 0 0 0 0 6
1 3 1 1 3 1
2 0 2 0 0 2
0 0 4 3 1 1
*/
int Height, Width;
int stRow, stCol;
int L;
int MAP[55][55];
//  상하좌우
int visited[55][55] = { 0, }; // 해당 좌표를 '찾은적 있는가?'

int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };
int d[8][4] = {
    {0, 0, 0, 0}, // <- 빈칸은 갈 수 없음
    {1, 1, 1, 1}, // <- 1번 터널
    {1, 1, 0, 0}, // <- 2번 터널
    {0, 0, 1, 1}, // <- 3번 터널
    {1, 0, 0, 1}, // <- 4번 터널
    {0, 1, 0, 1}, // <- 5번 터널
    {0, 1, 1, 0}, // <- 6번 터널
    {1, 0, 1, 0}  // <- 7번 터널
};
void init() {
    Height = Width = 0;
    stRow = stCol = 0;
    L = 0;
    memset(MAP, 0, sizeof(MAP));
    memset(visited, 0, sizeof(visited));
}
void input() {
    cin >> Height >> Width;
    cin >> stRow >> stCol;
    stRow += 1; stCol += 1; // 입력 : 0,0부터 시작 => 실사용 : 1,1부터 시작
    cin >> L;
    for (int i = 1; i <= Height; i++) //<- 0,Height-1 => 1,Height
        for (int j = 1; j <= Width; j++)
            cin >> MAP[i][j]; // <- 1.그래프 구성
}

void bfs() {
    // bfs작성시 문제될 수 있는 부분
    // 1. 2차원 맵에선 맵을 벗어나는 좌표?
    // 2. 갔던 좌표를 다시 가는가?
    //   => 각 좌표를 '몇 번'만에 갈 수 있는가?


    // 2. queue생성
    queue<pair<int, int>> q; // <- 좌표를 pair로 묶어서 넣어줌
    // 3. 시작점 세팅
    q.push({ stRow, stCol });
    visited[stRow][stCol] = 1;

    // ----------
    // 7. queue가 비워질때까지
    while (!q.empty()) {
        // 4. now꺼내기
        auto now = q.front(); q.pop(); // <- 찾았던 점(갈 수 있었던 점)
        int nowDir = MAP[now.first][now.second]; // 내 터널 종류(방향)
        // 5. now->next찾기
        for (int i = 0; i < 4; i++) {
            int nr = now.first + dr[i];
            int nc = now.second + dc[i];
            int nextDir = MAP[nr][nc];
            // 지금 nowDir종류의 터널인데 i라는 방향으로 뚫려있는가?
            if (!d[nowDir][i]) continue;

            // now : 상,좌 => next : 하,우로 뚫려있는가?
            if (i % 2 == 0 && !d[nextDir][i + 1]) continue;
            // now : 하,우 => next : 상,좌로 뚫려있는가?
            if (i % 2 == 1 && !d[nextDir][i - 1]) continue;

            if (visited[nr][nc]) continue;

            // 6. next를 queue에 추가
            q.push({ nr, nc });
            visited[nr][nc] = visited[now.first][now.second] + 1;
        }
    }
}

int solution() {
    bfs(); // <- 각 파이프별로 어느 시간에 위치할 수 있는지 전부 기록
    int ans = 0;
    for (int r = 1; r <= Height; r++)
        for (int c = 1; c <= Width; c++)
            if (visited[r][c] && visited[r][c] <= L)
                // 갈 수 있는 파이프이고 L시간이내에 갈 수 있다.
                ans++;
    return ans;
}

int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        init();
        input();
        int ans = solution();
        cout << "#" << tc << " " << ans << "\n";
    }
}
