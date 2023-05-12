#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main() {
    int data, n; cin >> n;
    stack<int> s;
    string input;
    
    for(int i=0; i<n; i++) {
        cin >> input;
        
        if(input=="push") { cin >> data; s.push(data); }
       
        else if(input=="pop") {
            if(s.empty()){
                cout << "-1" << '\n';
            }
            else{
                cout << s.top() << '\n'; 
                s.pop();
            }
       }
       
       else if(input=="size") cout << s.size() << '\n';       
       
       else if(input=="empty") cout << s.empty() << '\n';
       
       else if(input=="top") cout << (s.empty() ? -1 : s.top()) << '\n';
    }
    
    return 0;
}
