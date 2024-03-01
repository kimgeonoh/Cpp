// https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV140YnqAIECFAYD

#include <iostream>
#include <string>

using namespace std;

char* arr;
int n;
string result;

void dfs(int cur) { // cur: 현재 탐색 중인 정점의 노드
    if (cur > n) return;

    dfs(cur * 2); // 왼쪽
    cout << arr[cur]; // 자신
    dfs(cur * 2 + 1); // 오른쪽
}

int main() {

    for (int tc = 1; tc <= 10; tc++) {
        cout << "#" << tc << " ";

        cin >> n;
        cin.ignore();
        arr = new char[n + 1];

        for (int i = 1; i <= n; i++) {
            string input;
            getline(cin, input);
            bool flag = false;
            for (char c : input) {
                if (flag) {
                    arr[i] = c;
                    break;
                }
                if (c == ' ') flag = true;
            }
        }

        dfs(1);
        cout << "\n";

        delete[] arr;
    }

    cout << result;

    return 0;
}
