#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main() {
    int n; cin >> n;
    stack<int> s;
    int cmp=0;
    string result;
    bool flag = 0;
    
    while(n--){
        int input; cin >> input;
        if(input>cmp){
            while(input>cmp){
                s.push(++cmp);
                result += "+";
            }
            s.pop();
            result += "-";
        }
        else {
            if(s.top()==input){
                s.pop();
                result += "-";
            }
            else{
                flag = 1;
            }
        }
    }
    
    
    if(flag==0){
        for(int i=0; i<result.size(); i++){
            cout << result[i] << '\n';
        }
    }
    else {
        cout << "NO";
    }
    
    return 0;
}
