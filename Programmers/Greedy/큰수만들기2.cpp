#include <iostream>
#include <deque>

using namespace std;

string solution(string number, int k) {
    string answer;

    deque<char> dq; // 만들 수 있는 가장 큰 수 저장하는 덱
    int n = number.size(), cnt = 0;
    for(int i = 0; i < n; i++) {
        // 가장 작은 자리수(back)가 현재 수보다 작은 경우 지우기
        while(!dq.empty() && number[i] > dq.back() && cnt < k) {
            dq.pop_back(); cnt++;
        }
        dq.push_back(number[i]);
    }

    while(dq.size() > (n-k)) dq.pop_back(); // k개만큼 지우지 못한 경우

    while(!dq.empty()) {
        answer += dq.front();
        dq.pop_front();
    }
    return answer;
}
