#include <bits/stdc++.h>

using namespace std;

int answer;
int dist, redist;
vector<int> v, rev;

int solution(string name) {
    
    for(int i=0; i<name.size(); i++){ // alpha
        if(name[i]>='N') answer += 26-(name[i]-'A');
        else answer += name[i]-'A';
        
        if(name[i]!='A') {
            v.push_back(1); 
            rev.push_back(1);
        }
    }
    
    if(name[0]!='A') {
        v.pop_back(); 
        rev.pop_back();
    }
    
    for(int i=1; i<name.size(); i++){ // cursor
        if(v.empty()) break;
        dist++;
        if(name[i]!='A') v.pop_back();
        
    }
    for(int i=name.size()-1; i>0; i--){
        if(rev.empty()) break;
        redist++;
        if(name[i]!='A') rev.pop_back();
        
    }
    
    if(dist<redist) answer += dist;
    else answer += redist;
    
    return answer;
}
