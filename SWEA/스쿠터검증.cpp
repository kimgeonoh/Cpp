#include <bits/stdc++.h>

using namespace std;

int T,answer;
int arr[9][9];

void test1(int r){ // 가로
    vector<int> v;
    for(int j=0; j<9; j++){
        v.push_back(arr[r][j]);
    }
    sort(v.begin(),v.end());
    for(int i=0; i<8; i++){
        if(v[i]==v[i+1]) answer = 0;
    }
}
void test2(int c){ // 세로
    vector<int> v;
    for(int i=0; i<9; i++){
        v.push_back(arr[i][c]);
    }
    sort(v.begin(),v.end());
    for(int i=0; i<8; i++){
        if(v[i]==v[i+1]) answer = 0;
    }
}
void test3(int r, int c){ // 3*3
    vector<int> v;
    int x = r;
    for(; r<x+3; r++){
        for(int j=0; j<3; j++){
            v.push_back(arr[r][c+j]);
        }
    }
    sort(v.begin(),v.end());
    for(int i=0; i<8; i++){
        if(v[i]==v[i+1]) answer = 0;
    }
}

int main() {
    cin >> T;
    for(int t=1; t<=T; t++){
        answer=1;
        for(int i=0; i<9; i++){
            for(int j=0; j<9; j++){
                cin >> arr[i][j];
            }
        }
        
        for(int i=0; i<9; i++) test1(i);
        for(int j=0; j<9; j++) test2(j);
        for(int m=0; m<9; m=m+3){
            for(int n=0; n<9; n=n+3){
                test3(m,n);
            }
        }
        cout << '#' << t << ' ' << answer << '\n'; // 겹쳐져있으면 0
    }
}
