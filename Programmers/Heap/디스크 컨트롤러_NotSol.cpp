#include <string>
#include <vector>
#include <queue>

using namespace std;

struct node{
    int start;
    int runtime;
    bool operator<(const node& left) const {
        if(runtime > left.runtime) return true;
        else{
            if(start > left.start) return true;
            return false;
        }
    }
};

int solution(vector<vector<int>> jobs) {
    int answer = 0;
    int time = 0;
    vector<int> result;
    priority_queue<node> pq;
    for(auto v : jobs) pq.push({v[0], v[1]});

    while(!pq.empty()){
        node now = pq.top();
        pq.pop();
        
        if(time >= now.start){
            result.push_back(now.runtime + time - now.start);
            time += now.runtime;
        }
        else{
            time = now.start + now.runtime;
            result.push_back(now.runtime);
        }
    }
    
    for(auto v : result) answer += v;
    answer /= result.size();
    
    return answer;
}
