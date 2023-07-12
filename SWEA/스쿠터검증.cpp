#include <bits/stdc++.h>

using namespace std;

int T,answer;
int arr[9][9];

void test1(int r){ // 가로
    
}
void test2(int c){ // 세로
    
}
void test3(){
    
}

int main() {
    cin >> T;
    for(int t=1; t<=T; t++){
        for(int i=0; i<9; i++){
            for(int j=0; j<9; j++){
                cin >> arr[i][j];
            }
        }
        
        for(int i=0; i<9; i++){
            test1(i);
        }
        for(int j=0; j<9; j++){
            test2(j);
        }
        
        test3(); // 3*3
        cout << '#' << t << ' ' << answer; // 정답일떄 1
    }
}
