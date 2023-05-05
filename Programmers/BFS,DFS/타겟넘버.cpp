#include <bits/stdc++.h>

using namespace std;

int answer;

void dfs(int i, int now, vector<int> numbers, int target){
    if(i == numbers.size()) {
        if(now == target) {
            answer++;
        }
        return;
    }
    
    dfs(i+1, now + numbers[i], numbers, target); // +
    dfs(i+1, now - numbers[i], numbers, target); // -
    
    return;
}

int solution(vector<int> numbers, int target) {
    
    int n = numbers.size();
    dfs(1,numbers[0],numbers,target);
    dfs(1,-numbers[0],numbers,target);
    
    return answer;
}
