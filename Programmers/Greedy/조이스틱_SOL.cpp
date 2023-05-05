#include <bits/stdc++.h>

using namespace std;

int answer;

int solution(string name) {
        
    int n = name.size();
    int min_move = n-1;
    
    for(int i=0; i<n; i++){ // alpha
        if(name[i]>='N') answer += 26-(name[i]-'A');
        else answer += name[i]-'A';
        
        int next = i + 1;
        while(next<n && name[next] == 'A') next++;
        
        min_move = min(min_move, i + n - next + min(i, n - next));
    }
    
    answer += min_move;
    
    return answer;
}
