#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool univ_flag = false;
int visit[10001];
vector<string> answer;

bool strcmp(string a, string b){ // 하나라도 글자가 다를 경우 true 리턴
    for(int i=0; i<3; i++){
        if(a[i] != b[i]) return true;
    }
    return false;
}

void dfs(string now, vector<vector<string>> tickets){
    bool flag = true;
    // 모든 visit를 다 돈 경우
    for(int i=0; i<tickets.size(); i++){
        if(visit[i] == 0) flag = false; 
    }
    if(flag || univ_flag) {
        univ_flag = true;
        return;
    }
    
    // now 의 다음 경로 찾아서 tmp 에 넣고 알파벳 순이므로 정렬을 통해 간다
    vector<pair<string,int>> tmp;
    for(int i=0; i<tickets.size(); i++){
        if(visit[i] == 1) continue;
        if(!strcmp(now, tickets[i][0])) {
            tmp.push_back( {tickets[i][1],i} );
        }
    }
    
    if(!tmp.empty()){
        sort(tmp.begin(), tmp.end());
        
        for(int i=0; i<tmp.size(); i++){
            visit[tmp[i].second] = 1;
            answer.push_back(tmp[i].first);
        
            dfs(tmp[i].first, tickets);
            if(univ_flag) return;
        
            visit[tmp[i].second] = 0;
            answer.pop_back();
        }
    }
    else{ // 갈 수 있는 경우가 없는 경우
        return;
    }
}

vector<string> solution(vector<vector<string>> tickets) {
    
    //vector<string> path;
    answer.push_back("ICN");
    dfs("ICN", tickets);
    
    return answer;
}
