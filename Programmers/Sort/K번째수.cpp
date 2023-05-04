#include <bits/stdc++.h>

using namespace std;

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
    vector<int> answer;
    
    int n = commands.size();
    
    for(int m=0; m<n; m++){
        vector<int> temp;
        int i = commands[m][0]; int j = commands[m][1]; int k = commands[m][2];
        while(i<=j){
            temp.push_back(array[i-1]);
            i++;
        }
        sort(temp.begin(), temp.end());
        answer.push_back(temp[k-1]);
    }
    
    return answer;
}
