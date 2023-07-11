#include <iostream>
#include <algorithm>

using namespace std;

const int MAX = 15;

int T,N,M,arr[MAX][MAX];
int dx[2][4] = { {-1, 0, 1, 0}, {-1, -1, 1, 1} }; // 2개 시도를 위한 dx,dy
int dy[2][4] = { {0, 1, 0, -1}, {-1, 1, 1, -1} };

int main() {
    int T; cin >> T;
    for(int t=1; t<=T; t++){
        cin >> N >> M;
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                cin >> arr[i][j];
            }
        }
        
        int max_v = 0, temp = 0;
        
        for (int x = 0; x < N; x++) {
            for (int y = 0; y < N; y++) {
                for (int i = 0; i < 2; i++) { // temp 2번 시도
                    temp = arr[x][y];
 
                    for (int k = 1; k < M; k++) {
                        for (int j = 0; j < 4; j++) {
                            int nx = x + dx[i][j] * k;
                            int ny = y + dy[i][j] * k;
 
                            if (nx >= 0 && nx < N && ny >= 0 && ny < N) temp += arr[nx][ny];
                        }
                    }
                    max_v = max(max_v, temp);
                }
            }
        }
        cout << "#" << t << ' ' << max_v << '\n';
    }
}
