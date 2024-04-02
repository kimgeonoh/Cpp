#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, K;
int dp[101][1001]; // dp[n][k], 1~n번 물건, k가방으로 얻을 수 있는 최대 가치
int w[101], v[101];
int ans;

int main() {
    int T;
    cin >> T;

    for (int testcase = 1; testcase <= T; testcase++) {
        cin >> N >> K;
        for (int i = 1; i <= N; i++) {
            cin >> w[i] >> v[i];
        }

        for (int i = 1; i <= N; i++) {
            for (int j = 0; j <= K; j++) {
                // i 번째 물건을 가방에 넣지 않는 경우에 대한 최대값
                dp[i][j] = dp[i - 1][j];
                // i 번째 물건을 가방에 넣는 경우에 대한 최대값 
                if (w[i] <= j && dp[i][j] < dp[i - 1][j - w[i]] + v[i]) {
                    dp[i][j] = dp[i - 1][j - w[i]] + v[i];
                }
            }
        }

        cout << "#" << testcase << " " << dp[N][K] << endl;
    }

    return 0;
}
