#include <bits/stdc++.h>

using namespace std;

vector<int> solution(vector<int> answers) {
    vector<int> answer;
    
    vector<int> n1 = {1,2,3,4,5};
    vector<int> n2 = {2,1,2,3,2,4,2,5};
    vector<int> n3 = {3,3,1,1,2,2,4,4,5,5};
    
    int sol1=0, sol2=0, sol3=0;
    
    for(int i=0; i<answers.size(); i++){
        if(n1[i%5]==answers[i]) sol1++;
        if(n2[i%8]==answers[i]) sol2++;
        if(n3[i%10]==answers[i]) sol3++;
    }
    
    int maxsol = max(sol1,max(sol2,sol3));
    
    if(maxsol==sol1) answer.push_back(1);
    if(maxsol==sol2) answer.push_back(2);
    if(maxsol==sol3) answer.push_back(3);
    
    return answer;
}
