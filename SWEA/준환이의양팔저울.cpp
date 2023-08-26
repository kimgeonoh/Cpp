#include <iostream>

using namespace std;

int N;
int cnt;
// 전체 누적합
int sum;
int arr[10];
int visited[10];
int fact[10]; // 1 ~ 9 까지의 factorial ( N! )
int expo[10]; // 1 ~ 9 까지의 exponential ( 2 ^ N )


// 1. 재귀가 언제까지 돌아야 하는가 level
// 2. 왼쪽 누적합
// 3. 오른쪽 누적합
void dfs(int level, int left, int right) {
    // 기저 조건
    if (level == N) {
        if (left >= right) cnt++;
        return;
    }

    // 만약 왼쪽 저울에 올린 추의 무게가 이미 절반 이상을 넘어간다면
    // 즉, 남은 추들로 만들어낼 수 있는 모든 경우의 수가 정답
    // 남은 건 볼 필요도 없다! -> 모두 카운팅
    if (left >= sum - left) {
        cnt += expo[N - level] * fact[N - level];
        return;
    }


    // 재귀 파트
    for (int i = 0; i < N; i++) {
        if (visited[i] == 1) continue;

        // 왼쪽에 추가하는 경우
        // 들어가기 전
        visited[i] = 1;
        // 들어가자
        dfs(level + 1, left + arr[i], right);
        // 돌아와서
        visited[i] = 0;

        // 만약 오른쪽에 올리자마자, 왼쪽 저울보다 무거워진다면 continue
        if (left < right + arr[i]) continue;

        // 오른쪽에 추가하는 경우
        // 들어가기 전
        visited[i] = 1;
        // 들어가자
        dfs(level + 1, left, right + arr[i]);
        // 돌아와서
        visited[i] = 0;
    }
}

int main() {
    int T;
    cin >> T;

    // 초기화
    fact[0] = 1;
    expo[0] = 1;

    for (int i = 1; i <= 9; i++) {
        fact[i] = fact[i - 1] * i;
        expo[i] = expo[i - 1] * 2;
    }

    for (int tc = 1; tc <= T; tc++) {        
        // 초기화
        cin >> N;
        cnt = 0;
        sum = 0;
        for (int i = 0; i < N; i++) visited[i] = 0;

        // 입력
        for (int i = 0; i < N; i++) {
            cin >> arr[i];
            sum += arr[i];
        }

        dfs(0, 0, 0);

        cout << "#" << tc << " " << cnt << '\n';
    }

    return 0;
}
