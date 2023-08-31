#include<iostream>
#include<cstring>
using namespace std;

int N, M;
int MAP[22][22];
void init() {
    N = M = 0;
    memset(MAP, 0, sizeof(MAP));
}
void input() {
    cin >> N >> M;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> MAP[i][j];
}
int solution() {
    int ans = 0;
    for(int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            // i,j를 중심으로 마름모를 키워갈 예정
            int sum = 0; // <- 현재 마름모안의 집들이 지불할 비용
            for (int size = 0; size < 2 * N; size++) {// 마름모의 거리

                for (int r = i - size; r <= i; r++) { // 마름모의 윗부분
                    int c = r + j - i + size; // 우측 상단
                    if(r >= 0 && c >= 0 && c < N)
                        sum += MAP[r][c] * M;
                    c = -r + (i - size) + j;//좌측 상단
                    if (r >= 0 && c >= 0 && c < N && r != i-size)
                        sum += MAP[r][c] * M;
                }

                for (int r = i + 1; r <= i + size; r++) {
                    int c = r + j - (size + i);
                    if(r < N && c >= 0 && c < N)
                        sum += MAP[r][c] * M;
                    c = -r + j + size + i;
                    if (r < N && c >= 0 && c < N && r != i + size)
                        sum += MAP[r][c] * M;
                }

                // 손해를 보는지 여부 체크
                if ((size + 1) * (size + 1) + size * size <= sum)
                    ans = max(ans, sum / M);
            }
        }
    return ans;
}

int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        init();
        input();
        int ans = solution();
        cout << "#" << tc << " " << ans << "\n";
    }
}
