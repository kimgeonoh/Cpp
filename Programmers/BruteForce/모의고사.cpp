#include <bits/stdc++.h>

using namespace std;

vector<int> solution(vector<int> answers) {
    vector<int> answer, one, two, three;
    int n = answers.size();
    int sol1=0,sol2=0,sol3=0;
    int two_arr[8]={0,1,0,3,0,4,0,5};
    int three_arr[10]={3,3,1,1,2,2,4,4,5,5};
    vector<pair<int,int>> result;
    
    int cnt=1;
    for(int i=0; i<n; i++){ // initial
        if(cnt==6) cnt=1;
        one.push_back(cnt++);
        
        if(i%2==0) two.push_back(2);
        else two.push_back(two_arr[i%8]);
        
        three.push_back(three_arr[i]);
    }
    
    for(int i=0; i<n; i++){ // check
        if(one[i]==answers[i]) sol1++;
        if(two[i]==answers[i]) sol2++;
        if(three[i]==answers[i]) sol3++;
    }
    
    result.push_back({sol1,1});result.push_back({sol2,2});result.push_back({sol3,3});
    sort(result.begin(),result.end());
    
    bool flag1 = 0, flag2 = 0;
    if(result[2].first == result[1].first) {
        flag1 = 1;
        if(result[1].first == result[0].first) {
            flag2 = 1;
        }
    }

    answer.push_back(result[2].second);
    if(flag1) {
        answer.push_back(result[1].second);
        if(flag2){
            answer.push_back(result[0].second);
        }
    }
    
    sort(answer.begin(), answer.end());
    
    return answer;
}
