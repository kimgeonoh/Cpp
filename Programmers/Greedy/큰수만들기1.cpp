#include <string>
#include <vector>
#include <stack>

using namespace std;

string solution(string number, int k) {
    string answer;
    stack<char> s;

    for (int i = 0; i < number.size(); i++) {
        char next = number[i];

        //스택이 비지 않았다면, 다음에 들어올 수보다 top이 더 작고 k가 남아있으면 stack의 값을 뺀다.
        if (!s.empty()) {
            while (s.top() < next && k > 0) {
                s.pop();
                k--;

                if (s.empty()) break; // break는 while문만 break한다.
            }
        }
        //스택에 지금 값을 넣는다.
        s.push(next);
    }

    for (int i = 0; i < k; i++) { // number를 다 돌았지만 k가 남아있는 경우 k개만큼 뺴준다
        s.pop();
    }

    //스택이 빌때까지 쌓인 수를 뺀다.
    while (!s.empty()) {
        char c = s.top();
        s.pop();
        //스택에서 나올 때 순서는 반대기 때문에 반대로 붙여준다.
        answer = c + answer;
    }
    return answer;
}
