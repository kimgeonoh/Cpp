#include <iostream>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

int main() {
    int n; cin >> n;
    
    vector<int> v;
    
    while(n--){
        string input; cin >> input;
        
        int m = input.size();
        
        for(int i=0; i<m; i++){
            queue<int> q;
            string temp;
            long long y;
            
            while(isdigit(input[i])){
                q.push(input[i]);
                if(i == m-1) break;
                i++;
            }
            while(!q.empty()){
                int x = q.front();
                q.pop();
                temp.push_back(x);
            }
            if(!temp.empty()) y = stoll(temp), v.push_back(y);
        }
    }
    
    sort(v.begin(), v.end());
    
    for(int i=0; i<v.size(); i++) cout << v[i] << '\n';
}
