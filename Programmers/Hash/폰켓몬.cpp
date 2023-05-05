#include <bits/stdc++.h>

using namespace std;

int answer,n,limit,pick;

int solution(vector<int> nums) {
    n = nums.size();
    limit = n/2;
    
    sort(nums.begin(), nums.end());
    
    for(int i=0; i<n; i++){
        if(nums[i]!=nums[i+1] && pick < limit) {
            pick++;
        }
    }
    
    answer = pick;
    
    return answer;
}
