#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
using namespace std;
/*
2
10
0 1 0 3 0 0 0 0 7 0
0 0 0 0 -1 0 5 0 0 0
0 4 0 0 0 3 0 0 2 2
1 0 0 0 1 0 0 3 0 0
0 0 3 0 0 0 0 0 6 0
3 0 0 0 2 0 0 1 0 0
0 0 0 0 0 1 0 0 4 0
0 5 0 4 1 0 7 0 0 5
0 0 0 0 0 1 0 0 0 0
2 0 6 0 0 4 0 0 0 4
6
1 1 1 1 1 1
1 1 -1 1 1 1
1 -1 0 -1 1 1
1 1 -1 1 1 1
1 1 1 1 1 1
1 1 1 1 1 1
*/

pair<int, int> wormHole[11][2];
// [wormhole번호][각 wormhole별로 2개] = 해당 웜홀의 위치

          //상,하,좌,우
int dr[] = {-1, 1, 0, 0};
int dc[] = { 0, 0,-1, 1};
int dir[6][4] = {
    { 0, 1, 2, 3}, // 빈칸
    {-1, 3, 0,-1}, // 1번 블록
    { 3,-1, 1,-1},
    { 2,-1,-1, 1},
    {-1, 2,-1, 0},
    {-1,-1,-1,-1}  // 5번 블록
};

int MAP[110][110];
int N;

void init() {
    N = 0;
    for (int i = 0; i < 110; i++)
        for (int j = 0; j < 110; j++)
            MAP[i][j] = 5; // 모든 곳이 벽이다.
}
void input() {
    cin >> N;
    int wormHoleCnt[11] = { 0, }; // wormhole별 발견한 개수
    for (int r = 1; r <= N; r++)
        for (int c = 1; c <= N; c++)
        {
            cin >> MAP[r][c];
            if (MAP[r][c] >= 6) { // 웜홀인 경우
                int cnt = wormHoleCnt[MAP[r][c]]; // 이번에 발견된 번호
                wormHole[MAP[r][c]][cnt] = {r, c};
                wormHoleCnt[MAP[r][c]]++; // 개수 counting
            }
        }
}

int simulation(int row, int col, int d) {
    // row, col에서 d라는 방향으로 공을 던졌을 때 시나리오
    int score = 0;
    int nowRow = row, nowCol = col, nowDir = d;
    // 현재 위치 및 방향
    while (true) {
        // 현재 진행 방향대로 움직이기
        nowRow += dr[nowDir];
        nowCol += dc[nowDir];
        int num = MAP[nowRow][nowCol];
        // 움직이면서 직면할 상황 3~4가지
        // 1. 블랙홀 <- 끝
        if (num == -1) return score;
        // 2. 시작좌표 <- 끝
        if (nowRow == row && nowCol == col) return score;
        // 3. 웜홀
        if (num >= 6) {
            auto A = wormHole[num][0];
            auto B = wormHole[num][1];
            pair<int, int> now = {nowRow, nowCol};
            if (A == now) { // A쪽 웜홀에 위치 => B로 이동
                nowRow = B.first; nowCol = B.second;
            }
            else { // B쪽 웜홀에 위치 => A로 이동
                nowRow = A.first; nowCol = A.second;
            }
        }
        // 4. 벽 or 빈칸
        else { // num이 5이하
            nowDir = dir[num][nowDir]; // 다음 방향
            if (nowDir == -1) return score*2 + 1; // 평평한 면을 만났다.

            if (num >= 1)
                score++;
        }
    }
}

int solution() {
    int maxScore = 0;
    for(int row = 1; row <= N; row++)
        for (int col = 1; col <= N; col++) {
            if (MAP[row][col]) // 빈 블록이 아니면 X
                continue;
            for (int d = 0; d < 4; d++) { // 4가지 방향으로 공을 던짐
                maxScore = max(maxScore, simulation(row, col, d));
            }
        }
    return maxScore;
}

int main() {

    //freopen("input.txt", "r", stdin);

    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        init();
        input();
        cout << "#" << tc << " " << solution() << "\n";
    }
}
