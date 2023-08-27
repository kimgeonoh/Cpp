#include <iostream>
#include <queue>

// 원본 생명력이 높은 순으로 정렬하고 먼저 bfs를 돌리게 되면 동시에 번식했을때 수정하는 프로세스를 진행시키지 않아도 된다.

using namespace std;

struct Cell {
    // 원본 생명력
    int origin_life;
    // 생명력
    int life;
    // 상태값 ( 0 : 죽은 상태 / 1 : 활성 상태 / 2 : 비활성 상태
    int state;
    // 좌표값
    int y, x;

    bool operator<(Cell right) const {
        // 1. 수명이 클수록 우선순위가 높다.
        if (origin_life < right.origin_life) return true;
        if (origin_life > right.origin_life) return false;

        // 선택의 영역 - 좌표값이 앞에 나올수록 우선순위가 높다.
        if (y > right.y) return true;
        if (y < right.y) return false;

        if (x > right.x) return true;
        if (x < right.x) return false;

        return false;
    }
};

int N, M, K;
int MAP[651][651];
int visited[651][651];
priority_queue<Cell> pq;
int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0 , 0, -1, 1 };

// 1 시간
void bfs() {
    // 한 시간 동안 사용할 임시 pq
    priority_queue<Cell> tmp_pq;
    while (!pq.empty()) {
        tmp_pq.push(pq.top());
        pq.pop();
    }

    while (!tmp_pq.empty()) {
        Cell now = tmp_pq.top();
        tmp_pq.pop();

        // 상태값 확인
        // 비활성 -> life-- / life 가 0 이면 활성 상태로 변경
        int new_life = now.life - 1;
        if (now.state == 2) {
            if (new_life > 0) {
                // 원본, 생명력, 상태값, y, x
                pq.push({ now.origin_life, new_life, now.state, now.y, now.x });
            }
            else {
                pq.push({ now.origin_life, now.origin_life, 1, now.y, now.x });
            }
        }
        // 활성 -> life-- / life 가 0 보다 크면 활성 상태로 유지 / 번식
        else {
            if (new_life > 0) {
                pq.push({ now.origin_life, new_life, now.state, now.y, now.x });
            }

            for (int i = 0; i < 4; i++) {
                int new_y = now.y + dy[i];
                int new_x = now.x + dx[i];

                if (new_y < 0 || new_y > 650) continue;
                if (new_x < 0 || new_x > 650) continue;
                if (visited[new_y][new_x] == 1) continue;

                visited[new_y][new_x] = 1;
                // 새로 번식될 세포
                pq.push({ now.origin_life, now.origin_life, 2, new_y, new_x });
            }
        }
    }
}

int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        // 초기화
        for (int i = 0; i < 651; i++) {
            for (int j = 0; j < 651; j++) {
                visited[i][j] = 0;
            }
        }
        while (!pq.empty()) pq.pop();

        // 입력
        cin >> N >> M >> K;

        for (int i = 300; i < 300 + N; i++) {
            for (int j = 300; j < 300 + M; j++) {
                cin >> MAP[i][j];
                // 최초 세포 상태
                if (MAP[i][j]) {
                    pq.push({ MAP[i][j], MAP[i][j], 2, i, j });
                    visited[i][j] = 1;
                }
            }
        }

        // K 시간 만큼 시간을 진행
        for (int i = 0; i < K; i++) {
            bfs();
        }

        cout << "#" << tc << " " << pq.size() << "\n";
    }

    return 0;
}
