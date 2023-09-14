#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

vector<int> find(vector<int> progresses, vector<int> speeds){
    vector<int> result;
    
    for(auto v : progresses) result.push_back(100 - v);
    for(int i=0; i<result.size(); i++) result[i] /= speeds[i];
    
    //for(auto v:result) cout << v << '\n';
    
    return result;
}

bool check(vector<int> answer, vector<int> progresses){
    int temp = 0;
    for(auto i : answer) temp += i;
    
    //cout << temp << '\n';
    if(temp == progresses.size()) return true;
    else return false;
}

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    
    vector<int> time = find(progresses, speeds);
    
    int clock = 0;
    queue<int> q;
    for(auto v : time) q.push(v);
    //while(1){
    //    if(check(answer, progresses)) break;
        
        while(!q.empty()){
            int now = q.front();
            
            temp++;
            if(now <= clock){
                q.pop();
                
            }
        }
    //}
    
    return answer;
}
