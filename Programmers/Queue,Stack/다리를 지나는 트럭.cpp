#include <string>
#include <vector>
#include <queue>
#include <deque>

using namespace std;

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int time = 0;
    queue<int> bridge; // time
    deque<int> wait;   // weight
    for(auto v : truck_weights) wait.push_back(v);
    int bridge_weight = 0;
    
    while(!bridge.empty() && !wait.empty()){
        
        // limit 당 다리에 트럭을 싣는다
        while(bridge.size() < bridge_length && bridge_weight < weight && (bridge_weight + wait.front()) < weight ){
            bridge.push(wait.front());
            bridge_weight += wait.front();
            wait.pop_front();
        }
        
        // 트럭의 시간이 경과한다, 다리에서 시간이 다 지난것은 없앤다
        int rep = bridge.size();
        while(rep--){
            int now = bridge.front(); bridge.pop();
            if(now > 2) continue;
            now += 1;
            bridge.push(now);
            // brdige_weight 를 빼자
        }
        // 시간이 지났다
        time++;
    }
    
    return time;
}
