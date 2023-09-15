#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>

using namespace std;

int solution(vector<int> priorities, int location) {
    
    int answer;
    queue<pair<int,int>> q;
    priority_queue<int> pq; // 최대값인지 확인
    for(int i=0; i<priorities.size(); i++){
        q.push( {priorities[i],i} );
        pq.push( priorities[i] );
    }

    int time = 1;
    while(!q.empty()){
        int max = pq.top();
        
        pair now = q.front();
        int value = now.first;
        int idx = now.second;
        q.pop();
        
        if(idx == location && max == value) {
            answer = time;
            break;
        }
        
        if(max == value) {
            pq.pop();
            time += 1;
        }
        else q.push(now);
    }
    
    
    return answer;
}
