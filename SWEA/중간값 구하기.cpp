#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 20171109;

int main() {
    
    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        // 중간값을 알기 위해서는 {49개의 수 < 중간값 < 49개의 숫} 를 충족하면 된다.  
        // 큰 바구니와 작은 바구니는 {대표값 조회, 삽입, 삭제} 기능을 해야하므로 O(1), O(log N) 의 속도로 효율적인 힙 자료구조를 이용한다
        priority_queue<int, vector<int>, greater<int>> minH; 
        priority_queue<int, vector<int>, less<int>> maxH;

        int N, A;
        cin >> N >> A;

        minH.push(A); // 큰 바구니가 항상 한개 더 많다. 그러므로 큰 바구니의 대표값이 항상 답이 되야한다.
        int answer = 0;

        for (int i = 0; i < N; i++) {
            int num1, num2;
            cin >> num1 >> num2;

            if (num1 > num2) {
                minH.push(num1);
                maxH.push(num2);
            } else {
                minH.push(num2);
                maxH.push(num1);
            }

            while (!minH.empty() && !maxH.empty() && minH.top() < maxH.top()) {
                int minVal = minH.top();
                int maxVal = maxH.top();
                minH.pop();
                maxH.pop();
                minH.push(maxVal);
                maxH.push(minVal);
            }

            answer = (minH.top() + answer) % MOD;
        }

        cout << "#" << t << " " << answer << endl;
    }

    return 0;
}
