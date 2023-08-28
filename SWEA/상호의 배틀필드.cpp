#include <iostream>


using namespace std;

int H, W;
// int 로 작성하고 변환해서 사용
char MAP[21][21];
char dirs[] = { '^', 'v', '<', '>' };
int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };
int starty, startx, dir;
int N;
// string 도 당연히 사용가능하다.
// 문제에서 최대 길이를 주었기 때문에, 간단하게 char 배열로 작성
char user_input[101];

void shoot() {
    // 전차 좌표 에서 전차가 바라보는 방향으로 직선을 확인하면서
    // 벽돌벽이면 평지로 변환
    int new_y = starty;
    int new_x = startx;

    while (true) {
        new_y += dy[dir];
        new_x += dx[dir];

        // 맵 밖으로 나갈 경우
        if (new_y < 0 || new_y >= H) return;
        if (new_x < 0 || new_x >= W) return;

        // 강철벽을 만날 경우
        if (MAP[new_y][new_x] == '#') return;

        // 물을 만날 경우
        // if (MAP[new_y][new_x] == '-') continue;

        // 벽돌벽을 만날 경우
        if (MAP[new_y][new_x] == '*') {
            // 평지로
            MAP[new_y][new_x] = '.';
            return;
        }
    }
}

// 이동
// 함수 하나에 끝내기
void move(char ui) {
    // 1. 방향 변경
    if (ui == 'U') dir = 0;
    else if (ui == 'D') dir = 1;
    else if (ui == 'L') dir = 2;
    else if (ui == 'R') dir = 3;

    // 방향 변경 적용
    MAP[starty][startx] = dirs[dir];

    // 2. 전차가 갈 수 있는가 체크
    // 갈 수 있을 때만 해당 방향으로 한 칸 이동

    int new_y = starty + dy[dir];
    int new_x = startx + dx[dir];

    // 맵 밖으로 나갈 경우
    if (new_y < 0 || new_y >= H) return;
    if (new_x < 0 || new_x >= W) return;

    // 갈 수 있는 경우
    if (MAP[new_y][new_x] == '.') {
        // 기존에 있던 곳을 평지로 변경
        MAP[starty][startx] = '.';
        // 이동
        MAP[new_y][new_x] = dirs[dir];

        // *전차 좌표를 변경*
        starty = new_y;
        startx = new_x;
    }
}

int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        // 초기화

        // 입력
        cin >> H >> W;

        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                cin >> MAP[i][j];

                if (MAP[i][j] == '^') starty = i, startx = j, dir = 0;
                else if (MAP[i][j] == 'v') starty = i, startx = j, dir = 1;
                else if (MAP[i][j] == '<') starty = i, startx = j, dir = 2;
                else if (MAP[i][j] == '>') starty = i, startx = j, dir = 3;
            }
        }
        
        cin >> N;

        for (int i = 0; i < N; i++) {
            cin >> user_input[i];
        }

        for (int i = 0; i < N; i++) {
            // 포탄 발사일 때
            if (user_input[i] == 'S') {
                shoot();
            }
            // 나머지 (이동일 때)
            else {
                move(user_input[i]);
            }
        }

        // 출력
        cout << "#" << tc << " ";
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                cout << MAP[i][j];
            }
            cout << "\n";
        }
    }
}
