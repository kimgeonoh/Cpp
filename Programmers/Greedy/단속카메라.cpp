#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(vector<int> a, vector<int> b){
    return a[1] < b[1];
}

int solution(vector<vector<int>> routes){
    int answer = 0;
    int visit[10000]{};
    int temp;
    
    sort(routes.begin(), routes.end(), cmp);
    
    for(int i=0; i<routes.size(); i++){
        if(visit[i]) continue;
        visit[i]=1;
        answer++;
        temp = routes[i][1];
        
        for(int j=i; j<routes.size(); j++){
            if(visit[j]) continue;
            if(routes[j][0] <= temp && temp <= routes[j][1]) visit[j] = 1;
        }
    }
    
    
    return answer;
}
