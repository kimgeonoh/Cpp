#include <bits/stdc++.h>

using namespace std;

int n,target;
vector<vector<int>> v(n, vector<int>(n));
//int arr[999][999];
int ansi,ansj;

int main() {
    cin >> n >> target;
    
    int cx = n/2;
    int cy = n/2;
    int d = 1;
    int number = 1;
    
    while(number <= n*n){
        
        for(int i=0; i<d; i++) v[cx--][cy] = number++;
        if(cx<0) break;
        for(int i=0; i<d; i++) v[cx][cy++] = number++;
        d++;
        for(int i=0; i<d; i++) v[cx++][cy] = number++;
        for(int i=0; i<d; i++) v[cx][cy--] = number++;
        d++;
    }
    
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << v[i][j] << ' ';
            if(v[i][j]==target) ansi = i+1, ansj = j+1;
        }
        cout << '\n';
    }
    
    cout << ansi << ' ' << ansj << '\n';
}
