#include <string>
#include <cstring>
#include <vector>
#include <iostream>

using namespace std;

// 변환이 불가능한경우?
// 1. words에 target 가 없는 경우
// 2. 2개 이상 철자를 바꿔야하는데 중간에 매개가 없어서 한개한개씩 못바꾸는 경우

int visit[51];
int answer = 1e9;

bool if_all_visit_one(int n){ // 모든 visit 를 탐색한 경우 true 리턴
    bool flag = true;
    
    for(int i=0; i<n; i++){
        if(visit[i] == 0) flag = false;
    }
    
    return flag;
}

bool one_change(string a, string b){ // 한 c만 다를 경우 true 리턴
    int cnt = 0;
    int n = a.size();
    
    for(int i=0; i<n; i++){
        if(a[i] != b[i]) cnt++;
    }
    
    if(cnt == 1) return true;
    else return false;
}

bool strcmp(string a, string b){ // a와 b가 같다면 false 을 리턴
    int n = a.size();
    
    for(int i=0; i<n; i++){
        int tmp_cnt = a[i] - b[i];
        if(tmp_cnt != 0) return 1;
    }
    
    return 0;
}

void dfs(string now, string target, vector<string> words, int result){
    
    //cout << now << '\n';
    
    if(!strcmp(now, target)) { // target을 발견한 경우
        answer = min(answer,result);
        return;
    }
    if(if_all_visit_one(words.size())) return; // 모든 visit 를 뒤져도 못 발견한 경우
    
    for(int i=0; i<words.size(); i++){
        if(visit[i] == 1) continue;
        if(!one_change(now, words[i])) continue; // now에서 words와 한 c 만 차이나는지 검사
        
        visit[i] = 1;
        dfs(words[i], target, words, result + 1);
        visit[i] = 0; // 다양한 경로 탐색
    }
}

int solution(string begin, string target, vector<string> words) {
    bool flag = false;
    
    for(auto str : words) {
        if(!strcmp(str, target)) {
            dfs(begin, target, words, 0);
            flag = true;
            break;
        }
    }
    
    if(!flag) answer = 0;
        
    return answer;
}
