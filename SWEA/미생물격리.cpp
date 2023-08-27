// 1번째 풀이
// temp인 q를 이용해 pointer로서 작동한다
// dq에 값이 저장되어 있으므로 pointer를 이용해 접근할 수 있다
// 접근한 값을 pq에 넣고 bfs를 돌린다. 이 결과를 q,dq에 다시 저장하고 반복한다

#include <iostream>
#include <queue>
#include <deque>
#include <algorithm>

using namespace std;

int T, n, m, k; // 격자공간 n, 격리시간 m, 미생물 군집 개수 k

int dx[4] = { -1,1,0,0 }; // 상하좌우
int dy[4] = { 0,0,-1,1 };

struct fight {
    int n;
    int dir;
    int t;
};

struct node {
    int x;
    int y;
    int number;
    int dir;
    int t;
    bool operator<(const node& left) const {   // max heap  
        if (number < left.number) return true;
        return false;
    }
};

deque<fight> dq[100][100];
priority_queue<node> pq;
queue<pair<int,int>> temp;

void bfs() {
    while (!temp.empty()) {
        int fx = temp.front().first;
        int fy = temp.front().second;
        int fn = dq[fx][fy].back().n;
        int fd = dq[fx][fy].back().dir;
        int ft = dq[fx][fy].back().t;
        temp.pop();
        pq.push({ fx,fy,fn,fd,ft });
    }

    while (!pq.empty()) {
        node now = pq.top();
        pq.pop();
        dq[now.x][now.y].pop_front();

        int nx = now.x + dx[now.dir];
        int ny = now.y + dy[now.dir];
        int nt = now.t + 1;

        // 오염 구역에 들어간 경우
        if (nx == 0 || nx == n-1 || ny == 0 || ny == n-1) {
            // 방향 전환
            int nd = now.dir + 1; // 1 상 2 하 3 좌 4 우
            if (nd % 2 == 0) nd -= 1; // 짝수
            else nd += 1;

            // 절반이 사망
            int nn = now.number / 2;

            temp.push({ nx, ny });
            dq[nx][ny].push_back({nn, nd - 1, nt});
        }

        // 오염 구역에 들어가지 않은 경우
        else {
            // 합치는 경우
            if (!dq[nx][ny].empty() && dq[nx][ny].back().t == nt) {
                // 열등한 경우
                if (dq[nx][ny].back().n >= now.number) {
                    dq[nx][ny].back().n += now.number;
                }
                // 우등한 경우, pq를 이용해서 무조건 먼저 실행된다.
                else {
                    dq[nx][ny].push_back({ now.number, now.dir, nt });
                    temp.push({ nx,ny });
                }
            }
            // 합치지 않는 경우
            else {
                // 비어있는 곳에 이동
                //if (dq[nx][ny].back().n == 0) {
                //    dq[nx][ny].push_back({ now.number, now.dir, nt });
                //    q.push({ nx,ny,now.number,now.dir,nt });
                //}
                // 비어있지 않은 곳에 이동, cross
                //else {
                    dq[nx][ny].push_back({ now.number, now.dir, nt });
                    temp.push({ nx,ny });
                //}
            }
        }
    }
}

int main() {
    cin >> T;
    for (int t = 1; t <= T; t++) {
        // 초기화
        int x, y, number, dir;
        int answer = 0;
        for (int i = 0; i < 100; i++) {
            for (int j = 0; j < 100; j++) {
                dq[i][j].clear();
            }
        }
        while (!pq.empty()) pq.pop();
        while (!temp.empty()) temp.pop();

        cin >> n >> m >> k;
        for (int i = 0; i < k; i++) {
            // dir 1 상 2 하 3 좌 4 우
            cin >> x >> y >> number >> dir;
            dir -= 1;
            temp.push({ x,y });
            dq[x][y].push_back({number,dir,1});
        }

        // array 약품화
        /*for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 || i == n - 1) arr[i][j] = 1;
                if (j == 0 || j == n - 1) arr[i][j] = 1;
            }
        }*/

        for (int i = 0; i < m; i++) bfs();

        while (!temp.empty()) {
            int fx = temp.front().first;
            int fy = temp.front().second;
            answer += dq[fx][fy].front().n;
            temp.pop();
        }
        
        cout << "#" << t << " " << answer << '\n';
    }
}

/*
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>

using namespace std;

struct info {
    int y, x, num, dir, idx;
    bool isAlive;
};

int n, m, k;
info temp;

vector<info> arr[100][100];
info infos[1000];

int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };

bool isWall(int y, int x) {
    return y == 0 || y == n - 1 || x == 0 || x == n - 1;
}

int changeDir(int dir) {
    if (dir == 0 || dir == 1) {
        return (dir + 1) % 2;
    }
    else if (dir == 2 || dir == 3) {
        return 2 + (dir + 1) % 2;
    }
}

int main(int argc, char** argv)
{
    int test_case;
    int T;

    freopen("input.txt", "r", stdin);
    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case)
    {
        // 입력
        cin >> n >> m >> k;
        for (int i = 0; i < k; i++) {
            cin >> temp.y >> temp.x >> temp.num >> temp.dir;
            temp.dir--; temp.idx = i; temp.isAlive = true;

            infos[temp.idx] = temp;
        }

        // m번의 이동
        int nextY, nextX;

        for (int i = 0; i < m; i++) {

            // 1. 모든 미생물 이동
            for (int idx = 0; idx < k; idx++) {

                // 살아 있으면 이동
                if (infos[idx].isAlive) {

                    nextY = infos[idx].y + dy[infos[idx].dir];
                    nextX = infos[idx].x + dx[infos[idx].dir];

                    infos[idx].y = nextY;
                    infos[idx].x = nextX;


                    if (isWall(nextY, nextX)) {
                        infos[idx].num /= 2;
                        infos[idx].dir = changeDir(infos[idx].dir);

                        if (infos[idx].num <= 0) {
                            infos[idx].isAlive = false;
                        }
                    }


                    if (infos[idx].isAlive) {
                        arr[infos[idx].y][infos[idx].x].push_back(infos[idx]);
                    }
                }
            }


            // 2. 같은 위치 미생물 합치기
            for (int y = 0; y < n; y++) {
                for (int x = 0; x < n; x++) {

                    if (!arr[y][x].empty()) {
                        int max = 0, max_idx = 0;

                        // 최댓값 찾기
                        for (int idx = 0; idx < arr[y][x].size(); idx++) {
                            if (max < arr[y][x][idx].num) {
                                max = arr[y][x][idx].num;
                                max_idx = arr[y][x][idx].idx;
                            }
                        }

                        info max_info = infos[max_idx];

                        // 모든 미생물 빼주면서
                        while (!arr[y][x].empty()) {
                            info pop = arr[y][x].back(); arr[y][x].pop_back();

                            // 최대값이 아닌 미생물은 죽이고 최대 군집에 추가
                            if (pop.num != max) {
                                max_info.num += infos[pop.idx].num;

                                pop.y = -1;
                                pop.x = -1;
                                pop.dir = -1;
                                pop.num = 0;
                                pop.isAlive = false;
                                infos[pop.idx] = pop;
                            }
                        }

                        infos[max_idx] = max_info;
                    }
                }
            }

        }

        // 총 군집 개수 세기
        int answer = 0;

        for (int idx = 0; idx < k; idx++) {
            if (infos[idx].isAlive) {
                answer += infos[idx].num;
            }
        }
        cout << "#" << test_case << " " << answer << endl;

        // 초기화
        for (int i = 0; i < k; i++) {
            infos[i].y = 0;
            infos[i].x = 0;
            infos[i].num = 0;
            infos[i].dir = -1;
            infos[i].isAlive = false;
        }
    }
    return 0;
}
*/
