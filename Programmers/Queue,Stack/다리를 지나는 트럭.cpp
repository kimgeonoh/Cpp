#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <iostream>

using namespace std;

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int time = 0;
    queue<pair<int,int>> bridge; // {weight, time}
    deque<int> wait;   // weight
    for(auto v : truck_weights) wait.push_back(v);
    int bridge_weight = 0;
    
    while(!bridge.empty() || !wait.empty()){
        
        // 트럭의 1시간이 경과한다, 다리에서 시간이 다 지난것은 없앤다
        int rep = bridge.size();
        while(rep--){
            pair now = bridge.front(); bridge.pop();
            int next = now.second + 1;
            if(next > bridge_length) {
                bridge_weight -= now.first;
                continue;
            }
            bridge.push({now.first, next});
        }
        
        // limit 당 다리에 트럭을 싣는다
        if(!wait.empty()) {
            if(bridge.size() < bridge_length && (bridge_weight + wait.front()) <= weight){
                bridge.push({wait.front(), 1});
                bridge_weight += wait.front();
                wait.pop_front();
            }
        }
        
        // 시간이 지났다
        time += 1;
        //cout << time << '\n';
    }
    
    return time;
}
