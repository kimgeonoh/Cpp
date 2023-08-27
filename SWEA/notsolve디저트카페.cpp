#include<iostream>
#include<vector>
using namespace std;

int N;
int M[30][30];

//        우하 좌하 좌상 우상 <- 사각형을 만들 방향 순서대로
int dr[] = { 1,  1, -1, -1 };
int dc[] = { 1, -1, -1,  1 };
int visited[110]; // index : 디저트 종류, value : 경로상에 있는 디저트인가?
int destRow, destCol; // 시작점의 바로 좌하단 점(사각형이되는 마지막 점)
vector<int> path;
int ans;

void input() {
    // 초기화 조심!!!!!!
    ans = 0;
    path.clear();
    for (int i = 0; i < 110; i++)
        visited[i] = 0;

    for (int i = 0; i < 30; i++)
        for (int j = 0; j < 30; j++)
            M[i][j] = -1;

    cin >> N;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            cin >> M[i][j]; //<- 1,1부터 시작하는 이유?

}

void dfs(int row, int col, int dir) { // row,col 좌표에서 dir 방향으로 진행중이다.
    if (row == destRow && col == destCol) {
        if (ans < path.size())
            ans = path.size(); // 최대 경로의 길이
        return; // 사각형 완성!
    }
    for (int ndir = dir; ndir <= dir + 1; ndir++) {
        // ndir == dir : 방향 그대로, ndir == dir + 1 : 방향을 꺾기
        
        if (ndir >= 4) continue; // 이미 다 꺾어봤다.
        int nr = row + dr[ndir];
        int nc = col + dc[ndir];

        if (M[nr][nc] == -1) continue; // 맵을 벗어나는 좌표
        if (visited[M[nr][nc]] == 1) continue; // 이미 들렸던 디저트 종류

        visited[M[nr][nc]] = 1;
        path.push_back(M[nr][nc]); // 경로에 등록

        dfs(nr, nc, ndir); // nr, nc좌표에서 ndir방향으로 진행해라!(가라!)

        // 복구 <- 다양한 경로
        path.pop_back(); // 경로에서 삭제
        visited[M[nr][nc]] = 0;
    }
}

void solution() {
    // 다양한 경로를 모두 해보기
    for (int row = 1; row <= N; row++)
        for (int col = 1; col <= N; col++)
        {
            destRow = row + 1;
            destCol = col - 1;

            visited[M[row][col]] = 1;
            path.push_back(M[row][col]);

            dfs(row, col, 0);

            path.pop_back();
            visited[M[row][col]] = 0;
        }
    if (ans < 4)
        ans = -1; // 4칸 이하면 사각형이 만들어진게 아니니 -1
}

int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        input();
        solution();
        cout << "#" << tc << " " << ans << "\n";
    }
    return 0;
}
