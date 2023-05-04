#include <bits/stdc++.h>

using namespace std;

string solution(string s) {
    string answer = "";
    int min = 2e9;
    int max = -2e9;
    string temp = "";
    vector<int> nums;
    for(int i = 0; i<=s.size(); ++i){
        if(s[i]==' ' || i==s.size()){
            nums.push_back(stoi(temp));
            temp = "";
        }
        else temp+=s[i];
    }
    for(int i = 0; i<nums.size(); ++i){
        if(nums[i]<min) min = nums[i];
        if(nums[i]>max) max = nums[i];
    }
    temp = to_string(min);
    answer += temp;
    answer += ' ';
    temp = to_string(max);
    answer += temp;
    return answer;
}
