#include<iostream>
#include<vector>
#include<algorithm> // max, min 함수 존재(2개씩만 비교 가능)

using namespace std;

// D : 두께     <- rowSize
// W : 가로크기 <- colSize
// K : 합격기준
int D, W, K;
int film[15][25];
int ans = 2134567890;
int cnt; // 약품 사용 개수

void input() {
    ans = 2134567890;
    cnt = 0;

    cin >> D >> W >> K;
    for (int row = 0; row < D; row++)
        for (int col = 0; col < W; col++)
            cin >> film[row][col];
}

vector<int> path; // 층별로 약품을 어떻게 처리할지?

bool isValid() { // 지금 path대로 처리하면 가능?
    // 세로 하나 select
    for (int col = 0; col < W; col++) {
        int cont = 1; // 지금까지 연속한 개수
        int prev = film[0][col]; // 맨 위의 특성
        if (path[0] != -1) prev = path[0]; // 맨 위가 약품처리되면 그 약품으로

        int contMax = 1; // 연속한 개수의 최댓값

        for (int row = 1; row < D; row++)
        {
            int nowValue = film[row][col];
            if (path[row] != -1) // 약품을 뽑았었다면
                nowValue = path[row]; // 약품처리

            if (prev == nowValue) // 이전과 같은 특성이면 연속
                cont++;
            else
                cont = 1;

            prev = nowValue;
            contMax = max(contMax, cont);
        }
        if (contMax < K) 
            return false; // 합격기준 미달
    }
    // 모든 세로줄이 합격기준 미달이 아니다.
    return true; // 합격기준에 부합
}

void func(int now) {
    // now층에서 약품을 어떻게 할 것인지
    
    if (now >= D) { // 끝까지 내려왔으면 멈춰!!!!
        // 0 ~ D-1층까지 뽑기 완료(D개의 층의 뽑기 완료)

        // 이번에 뽑은(약품을 처리하는) 방식으로 합격 기준에 부합하는가?
        if (isValid()) // 가능?가능?
            ans = min(ans, cnt);
        return;
    }


    // i는 약품을 어떻게 할 것인가?
    // i == -1 : 약품 사용 X
    // i == 0  : A약품
    // i == 1  : B약품
    for (int i = -1; i <= 1; i++) 
    {
        if (i != -1 && cnt + 1 > K) continue; // K개 붙여서 같게 만들면 끄읏이라 더 필요 X
        if (i != -1 && cnt + 1 >= ans) continue; // 이미 구한 답보다 더 많이 필요?

        if (i != -1) cnt++; // 약품개수 counting
        path.push_back(i);

        func(now + 1);

        if (i != -1) cnt--; // 약품개수 복구
        path.pop_back();
    }
}

void solution() {
    func(0);
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
