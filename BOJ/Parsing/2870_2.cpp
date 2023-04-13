#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool cmp(string a, string b){
    if(a.size() == b.size()) return a < b;
    return a.size() < b.size();
}

int main() {
    int n; cin >> n;
    
    vector<string> v;
    string temp;
    
    while(n--){
        string input; cin >> input;
        
        int m = input.size();
        
        for(int i=0; i<m; i++){
            if(isdigit(input[i])){
                if(temp.size() == 1 && temp == "0") temp = "";
                temp += input[i];
                if(i == m-1) v.push_back(temp), temp = "";
            }
            else{
                if(temp != "") v.push_back(temp);
                temp = "";
            }
        }
    }
    
    sort(v.begin(), v.end(), cmp);
    
    for(int i=0; i<v.size(); i++) cout << v[i] << '\n';
}
