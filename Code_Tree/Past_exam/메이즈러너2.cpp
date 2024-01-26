#include <iostream>
#include <queue>

using namespace std;

struct Node {
    int row, col, num, exit;
};

int N, M, K;
int arr[12][12] = { 0, };
Node entry[12] = { 0, };
int out_row, out_col;

int dist(int row, int col) {
    return abs(col - out_col) + abs(row - out_row);
}

struct Move {
    int row, col, num;

    bool operator<(Move right) const {
        if (num < right.num) return false;
        if (num > right.num) return true;

        if (dist(row, col) < dist(right.row, right.col)) return false;
        if (dist(row, col) > dist(right.row, right.col)) return true;

        return false;
    }
};

void input() {
    cin >> N >> M >> K;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> arr[i][j];
        }
    }
    for (int i = 0; i < M; i++) {
        cin >> entry[i].row >> entry[i].col;
    }
    cin >> out_row >> out_col;
    arr[out_row][out_col] = -1;
}


//회전
void rotation() {
    //사각형 찾기
    int sr1, sr2, sc1, sc2;
    int n = 1;
    while (1) {
        int square_flag = 0;

        for (int i = n; i >= 0; i--) {
            for (int j = n; j >= 0; j--) {
                int r1 = out_row - i;
                int r2 = r1 + n;
                int c1 = out_col - j;
                int c2 = c1 + n;
                if (r1<1 || c1<1 || r2>N || c2>N) continue;

                for (int k = 0; k < M; k++) {
                    Node now = entry[k];
                    if (now.exit == 1) continue;

                    //사각형 확정
                    if (now.row >= r1 && now.row <= r2 && now.col >= c1 && now.col <= c2) {
                        sr1 = r1;
                        sr2 = r2;
                        sc1 = c1;
                        sc2 = c2;
                        square_flag = 1;
                        break;
                    }
                }
                if (square_flag == 1) break;
            }
            if (square_flag == 1) break;
        }
        if (square_flag == 1) break;
        n++;
    }
    n++;
    int copy[12][12] = { 0, };
    //돌리기
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            copy[i][j] = arr[sr2 - j][sc1 + i];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            arr[sr1 + i][sc1 + j] = copy[i][j];
        }
    }

    //사람 위치도 바꿔주기
    for (int i = 0; i < M; i++) {
        Node now = entry[i];
        if (now.exit == 1) continue;
        if (now.row >= sr1 && now.row <= sr2 && now.col >= sc1 && now.col <= sc2) {
            int r = now.row - sr1;
            int c = now.col - sc1;
            entry[i].row = c + sr1;
            entry[i].col = n - r - 1 + sc1;
        }
    }
    //내구도 -1 해주기
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (arr[sr1 + i][sc1 + j] == -1) {
                out_row = sr1 + i;
                out_col = sc1 + j;
            }
            if (arr[sr1 + i][sc1 + j] >= 1 && arr[sr1 + i][sc1 + j] <= 9) arr[sr1 + i][sc1 + j]--;
        }
    }
}

//이동
void move() {
    for (int i = 0; i < M; i++) {
        Node now = entry[i];

        //탈출한 사람 제외
        if (now.exit == 1) continue;

        int dr[] = { -1,1,0,0 };
        int dc[] = { 0,0,-1,1 };
        
        priority_queue <Move> move;
        for (int j = 0; j < 4; j++) {
            int next_row = now.row + dr[j];
            int next_col = now.col + dc[j];

            if (next_row<1 || next_col<1 || next_row>N || next_col>N) continue;
            //벽
            if (arr[next_row][next_col] >= 1 && arr[next_row][next_col] <= 9) continue;
            //최단거리 더 짧은 곳만
            if (dist(now.row, now.col) < dist(next_row, next_col)) continue;
            move.push({ next_row, next_col, i });
        }
        if (move.empty()) continue;
        else {
            Move next = move.top();
            entry[i].row = next.row;
            entry[i].col = next.col;
            entry[i].num += 1;
            //탈출
            if (arr[next.row][next.col] == -1) entry[i].exit = 1;
        }
    }
}

int main() {

    input();
    for (int i = 0; i < K; i++) {

        move();
        //참가자들이 K초 이전 모두 탈출했는지 확인
        int flag = 0;
        for (int j = 0; j < M; j++) {
            if (entry[j].exit == 0) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) break;

        rotation();

    }

    int result = 0;
    for (int i = 0; i < M; i++) {
        result += entry[i].num;
    }
    cout << result << endl;
    cout << out_row << " " << out_col;
    
    return 0;
}
