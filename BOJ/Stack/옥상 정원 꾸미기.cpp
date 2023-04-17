#include <bits/stdc++.h>

using namespace std;

int N;
long long h;
vector<long long> v; // build height
stack<int> s;
int answer[80000];
int result;

int main() {
    cin >> N;
    for(int i=0; i<N; i++){
        cin >> h; 
        v.push_back(h);
        cout << h << '\n';
    }
    
    for(int i=0; i<N; i++){
        
        while(!s.empty() && v[i] >= v[s.top()]){ // 더이상 앞을 볼 수 없는 경우 체크
            answer[s.top()] = i - s.top() -1;
            s.pop();
        }
        
        s.push(i); // 인덱스를 넣는다
        if(i==N-1) s.pop(); // 마지막 인덱스는 스택에 넣지 않는다
    }
    
    while(!s.empty()) { // 전부 볼 수 있어서 스택에 남아있는 경우
        result += (N - 1 - s.top());
        s.pop();
    }
    
    for(int i=0; i<80000; i++) {
        result += answer[i];
    }
    
    cout << result << '\n';
}
