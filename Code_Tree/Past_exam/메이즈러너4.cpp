/*
메이즈 러너

미로 탈출게임
M 명의 참가자

1. 미로 N x N 격자
  각 위치는 (r, c), 좌상단 (1, 1)

2. 미로의 각 칸
  2-1.
  빈칸
    참가자 이동 가능
  2-2.
  벽
    참가자 이동 불가
    내구도 (1~9)
    회전시 내구도 1 감소
    내구도 0 = 빈칸
  출구
    참가자 탈출

1초마다 모든 참가자 한 칸 이동

이동, 움직이는 조건
  최단거리 |x1 - x2| + |y1 - y2|
  모든 참가자 동시 이동
  상하좌우 이동, 벽이 없는 곳(빈 칸)
  움직인 칸은 현재 머물러 있던 칸보다 출구까지 최단거리가 가까워야 한다.
  칸이 2개 이상이라면, 상하 이동이 우선
  참가자가 움직일 수 없는 상황이면, 이동 X
  한 칸에 2명 이상 참가자 가능

미로가 회전
  한 명 이상 참가자와 출구를 포함한 가장 작은 정사각형
  가장 작은 정사각형이 2개 이상이라면
    r 좌표가 작은 것이 우선,
    c 좌표가 작은 것이 우선

  선택된 정사각형
    시계 방향 90도로 회전 회전된 벽의 내구도 1 감소

K초 동안 위의 과정 반복
K초 전에 참가자 탈출 성공하면 게임 종료

모든 참가자들의 이동 거리 합과 출구 좌표 출력

입력

N M K
  N : 미로의 크기 (1 <= N <= 10)
  M : 참가자의 수 (1 <= M <= 10)
  K : 게임 시간 (1 <= K <= 100)

N x N 미로
  0 : 빈 칸
  1 ~ 9 : 벽

M개의 참가자 좌표, 초기 빈 칸에만 존재

출구의 좌표
*/

#define MAX 10
#include <iostream>

using namespace std;

struct Coord {
  int y, x;

  bool operator<(Coord right) const {
    if (y < right.y) return true;
    if (y > right.y) return false;

    if (x < right.x) return true;
    if (x > right.x) return false;

    return false;
  }
  bool operator>(Coord right) const {
    if (y > right.y) return true;
    if (y < right.y) return false;

    if (x > right.x) return true;
    if (x < right.x) return false;

    return false;
  }
};

struct Rect {
  int size;
  Coord coord;

  bool operator<(Rect right) const {
    if (size > right.size) return true;
    if (size < right.size) return false;

    if (coord > right.coord) return true;
    if (coord < right.coord) return false;

    return false;
  }
};

int dy[4] = {1, -1, 0, 0};
int dx[4] = {0, 0, 1, -1};

int N, M, K;
Coord pos_player[MAX];
Coord pos_exit;
bool is_exit[MAX];
int MAP[MAX][MAX];

int num_left;
int total_dist = 0;
int answer;

void input() {
  cin >> N >> M >> K;

  for (int j = 0; j < N; j++) {
    for (int i = 0; i < N; i++) {
      cin >> MAP[j][i];
    }
  }

  for (int i = 0; i < M; i++) {
    cin >> pos_player[i].y >> pos_player[i].x;
    pos_player[i].y -= 1;
    pos_player[i].x -= 1;
  }

  cin >> pos_exit.y >> pos_exit.x;

  pos_exit.y -= 1;
  pos_exit.x -= 1;

  return;
}

void playerMove() {
  int exit_y = pos_exit.y;
  int exit_x = pos_exit.x;

  for (int j = 0; j < M; j++) {
    if (is_exit[j]) continue;

    int y = pos_player[j].y;
    int x = pos_player[j].x;

    int dist = abs(y - pos_exit.y) + abs(x - pos_exit.x);

    bool movable = false;

    int ny, nx;

    for (int i = 0; i < 4; i++) {
      ny = y + dy[i];
      nx = x + dx[i];

      if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
      if (MAP[ny][nx]) continue;

      int ndist = abs(ny - pos_exit.y) + abs(nx - pos_exit.x);

      if (ndist < dist) {
        if (!ndist) {
          is_exit[j] = true;
          num_left--;
        }
        movable = true;
        break;
      }
    }

    if (!movable) continue;

    pos_player[j] = {ny, nx};
    total_dist++;
  }

  return;
}

void printMAP() {
  for (int j = 0; j < N; j++) {
    for (int i = 0; i < N; i++) {
      cout << MAP[j][i] << " ";
    }
    cout << "\n";
  }

  return;
}

void rotatePlayer(int target_y, int target_x, int target_size) {
  for (int k = 0; k < M; k++) {
    if (is_exit[k]) continue;

    if (pos_player[k].y < target_y || target_y + target_size <= pos_player[k].y)
      continue;
    if (pos_player[k].x < target_x || target_x + target_size <= pos_player[k].x)
      continue;

    int y = pos_player[k].y;
    int x = pos_player[k].x;

    int diff_y = y - target_y;
    int diff_x = x - target_x;

    pos_player[k].y = target_y + diff_x;
    pos_player[k].x = target_x + target_size - diff_y - 1;
  }

  return;
}

void rotateMAP(int target_y, int target_x, int target_size) {
  // cout << "===== BEFORE ROTATE =====\n";
  // printMAP();

  int MAP_copy[MAX][MAX] = {0};

  // COPY MAP
  for (int j = 0; j < target_size; j++) {
    for (int i = 0; i < target_size; i++) {
      MAP_copy[target_y + j][target_x + i] = MAP[target_y + j][target_x + i];
      if (MAP_copy[target_y + j][target_x + i])
        MAP_copy[target_y + j][target_x + i]--;
    }
  }

  // ROTATE
  for (int j = 0; j < target_size; j++) {
    for (int i = 0; i < target_size; i++) {
      MAP[target_y + j][target_x + i] =
          MAP_copy[target_y + target_size - 1 - i][target_x + j];
    }
  }

  if ((target_y <= pos_exit.y && pos_exit.y < target_y + target_size) &&
      (target_x <= pos_exit.x && pos_exit.x < target_x + target_size)) {
    int y = pos_exit.y;
    int x = pos_exit.x;

    int diff_y = y - target_y;
    int diff_x = x - target_x;

    pos_exit.y = target_y + diff_x;
    pos_exit.x = target_x + target_size - 1 - diff_y;
  }

  // cout << "===== AFTER ROTATE =====\n";
  // printMAP();

  return;
}

void rotateMaze() {
  Rect target_rect = {N, {N, N}};

  int exit_y = pos_exit.y;
  int exit_x = pos_exit.x;

  for (int i = 0; i < M; i++) {
    if (is_exit[i]) continue;

    int y = pos_player[i].y;
    int x = pos_player[i].x;

    int rect_size = max(abs(y - exit_y), abs(x - exit_x)) + 1;

    int max_y = max(y, exit_y);
    int max_x = max(x, exit_x);

    int rect_y = max_y > rect_size - 1 ? max_y - rect_size + 1 : 0;
    int rect_x = max_x > rect_size - 1 ? max_x - rect_size + 1 : 0;

    Rect temp_rect = {rect_size, {rect_y, rect_x}};

    if (target_rect < temp_rect) {
      target_rect = temp_rect;
    }
  }

  int target_y = target_rect.coord.y;
  int target_x = target_rect.coord.x;
  int target_size = target_rect.size;

  rotateMAP(target_y, target_x, target_size);
  rotatePlayer(target_y, target_x, target_size);

  return;
}

void solution() {
  num_left = M;

  for (int i = 0; i < K; i++) {
    playerMove();
    if (!num_left) break;
    rotateMaze();

    /*
    cout << "===== MAP AT: " << i + 1 << " =====\n";
    printMAP();
    */
  }

  answer = total_dist;
}

int main(int argc, char** argv) {
  input();
  solution();

  cout << answer << "\n";
  cout << pos_exit.y + 1 << " " << pos_exit.x + 1 << "\n";

  return 0;
}
