#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
1
5
20 3
2 2 3 2 2 2 2 3 3 4 4 3 2 2 3 3 3 2 2 3
4 4 1 4 4 1 4 4 1 1 1 4 1 4 3 3 3 3 3 3
4 4 1 100
7 10 3 40
6 3 2 70
*/

struct BC {
    int row, col;
    int range, P;
};

int M, A;
vector<int> pos[2]; // [who] [time] 에 따른 움직임 상황
vector<BC> bc;      // bc 정보
vector<vector<vector<int>>> graph; // [who 2개], [time n+1개] -> 충전 가능한 bc들(index)

void init() {
    M = A = 0;
    bc.clear();
}

void input() {
    cin >> M >> A;
    graph = vector<vector<vector<int>>>(2, vector<vector<int>>(M + 1)); // M 정보를 받고 생성하므로 초기화 할 필요가 없다
    pos[0] = vector<int>(M + 1); // M개크기로 생성
    pos[1] = vector<int>(M + 1); // M개크기로 생성

    for (int i = 0; i < 2; i++) {
        pos[i][0] = 0; // 그자리 그대로 있다
        for (int j = 1; j <= M; j++) {
            cin >> pos[i][j]; // i번사람이 j라는 시간에 이동하는 방향
        }
    }
    bc.push_back({ 0,0,500,0 }); // 초기화
    for (int i = 0; i < A; i++) {
        int row, col, range, P;
        cin >> col >> row >> range >> P;
        bc.push_back({ row, col, range, P });
    }
}

int dr[5] = { 0,-1,0,1,0 }; // 제자리 정지 포함
int dc[5] = { 0,0,1,0,-1 };

void makeGraph(int time, int who, int row, int col) { 
    // DFS
    // 시간별로 겹치는 영역들 찾기
    //time라는 시간에 who라는 사람이 row, col에 있다.
    if (time > M) return;
    int nr = row + dr[pos[who][time]];
    int nc = col + dc[pos[who][time]];
    for (int i = 0; i <= A; i++) {    // 각 BC에 대해
        BC nowbc = bc[i];
        int dist = abs(nowbc.row - nr) + abs(nowbc.col - nc);
        if (dist <= nowbc.range)
            //nowbc를 충전 가능 <- who라는 사람이 time이라는 시간에 nowbc를 충전 가능
            graph[who][time].push_back(i); // i는 bc idx
    }
    makeGraph(time + 1, who, nr, nc); //다음 시간으로 가라!
}

int calcCharge(int time) {
    if (time > M)
        return 0;
    int maxCharge = 0;
    for (int i = 0; i < graph[0][time].size(); i++) {
        for (int j = 0; j < graph[1][time].size(); j++) {
            int A = graph[0][time][i];
            int B = graph[1][time][j];
            if (A == B) {
                maxCharge = max(maxCharge, bc[A].P); // 균등 분배
            }
            else {
                maxCharge = max(maxCharge, bc[A].P + bc[B].P); // 각자
            }
        }
    }

    int nextCharge = calcCharge(time + 1);
    return maxCharge + nextCharge;
}

int solution() {
    makeGraph(0, 0, 1, 1);   //0시간, 0사람 1,1시작
    makeGraph(0, 1, 10, 10); //0시간, 1사람 10,10시작
    return calcCharge(0);
}

int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        init();
        input();
        int ans = solution();
        cout << "#" << tc << " " << ans << endl;
    }

}
