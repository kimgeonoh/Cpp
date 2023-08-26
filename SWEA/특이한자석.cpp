#include <iostream>
#include <deque>
#include <cmath>
using namespace std;

// 자석이 4개,
// 0 번은 생략, 1 ~ 4번을 활용
deque<int> dq[5];
int K;
int turn_flag[5];

// idx 자석을 기점으로, 다른 자석들을 모두 돌려야하는 지 확인
void turn_check(int idx, int dir) {
    for (int i = 0; i < 5; i++) turn_flag[i] = 0;
    turn_flag[idx] = dir;
    // 왼쪽 체크
    for (int i = idx; i >= 2; i--) {
        // 다른 자성끼리 붙어있다면
        if (dq[i - 1][2] != dq[i][6]) {
            turn_flag[i - 1] = turn_flag[i] * -1;
        }
    }
    // 오른쪽 체크
    for (int i = idx; i < 4; i++) {
        if (dq[i][2] != dq[i + 1][6]) {
            turn_flag[i + 1] = turn_flag[i] * -1;
        }
    }
}

void right_turn(int idx) {
    dq[idx].push_front(dq[idx].back());
    dq[idx].pop_back();
}

void left_turn(int idx) {
    dq[idx].push_back(dq[idx].front());
    dq[idx].pop_front();
}

int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        // 초기화
        for (int i = 1; i <= 4; i++) dq[i].clear();

        // 입력
        cin >> K;
        for (int i = 1; i <= 4; i++) {
            for (int j = 0; j < 8; j++) {
                int num;
                cin >> num;
                dq[i].push_back(num);
            }
        }

        for (int i = 0; i < K; i++) {
            int idx, dir;
            cin >> idx >> dir;

            // 1. idx 자석 돌리기
            // 2. 왼쪽(0 ~ idx - 1) 자석 회전
            // 3. 오른쪽(idx + 1 ~ 4) 자석 회전
            // 필요한 함수
            // 1. 현재 자석을 기점으로 확인하여
            //        다른 자석까지 모두 돌려야하는 지 여부를 저장
            
            turn_check(idx, dir);

            // 2. idx 번 째 자석을 시계방향으로 돌리는 함수
            // 3. idx 번 째 자석을 반시계방향으로 돌리는 함수

            for(int j = 1; j < 5; j++) {
                if (turn_flag[j] == 1) {
                    right_turn(j);
                }
                else if (turn_flag[j] == -1) {
                    left_turn(j);
                }
            }
        }

        // 점수 계산
        int result = 0;
        for (int i = 1; i <= 4; i++) {
            if (dq[i][0]) result += pow(2, i - 1);
        }
        cout << "#" << tc << " " << result << "\n";
    }

    return 0;
}
