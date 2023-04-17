#include <string>
#include <stack>
#include <vector>

using namespace std;

vector<int> solution(vector<int> prices) {
    int n = prices.size();
    stack<int> s;
    vector<int> answer(n);
    
    for(int i = 0; i < n; i++){
        while(!s.empty() && prices[s.top()] > prices[i]){   // 이전과 가격을 비교할 수 있고 가격이 떨어진 경우
            int top = s.top(); 
            s.pop();
            answer[top] = i - top; // 가격이 떨어진 idx 체크
        }
        s.push(i); // index를 stack에 넣는다
    }
    
    while(!s.empty()){ // 가격이 안떨어진 idx 체크
        int top = s.top();
        s.pop();
        answer[top] = (n-1) - top;
    }
    
    return answer;
}
