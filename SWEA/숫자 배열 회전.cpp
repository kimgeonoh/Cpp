// // https://blog.naver.com/study_electronic/223037427040
// 유사한 문제: https://school.programmers.co.kr/learn/courses/30/lessons/60059, 해답: https://github.com/ndb796/python-for-coding-test/blob/master/12/4.cpp
// 시계방향, 반시계방향으로 돌리는 것은 n-1-i 가 아니라 n-1-j 로 바꾸면 된다. 본 문제에서는 시계방향으로 돌리고 유사문제는 반시계로 돌린다

#include <bits/stdc++.h>

using namespace std;

int T;

vector<vector<int>> rotate90degree(vector<vector<int>> v){
    
    int n = v.size();
    vector<vector<int>> result(n, vector<int>(n));
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            result[j][n-1-i] = v[i][j];
        }
    }
    return result;
}

vector<vector<int>> save(vector<vector<int>> v, vector<vector<int>> new_v, int start_point){
    int n = v.size();
    for(int i=0; i<n; i++){
        for(int j=start_point; j<start_point+n; j++){
            new_v[i][j] = v[i][j-start_point];
        }
    }
    return new_v;
}

void output(vector<vector<int>> new_v, int i, int start, int end){
    for(int j=start; j<end; j++){
        cout << new_v[i][j];
    }
    cout << ' ';
}

int main() {
    cin >> T;
    for(int t=1; t<=T; t++){
        
        int n; cin >> n;
        vector<vector<int>> v(n, vector<int>(n));    
        vector<vector<int>> new_v(n, vector<int>(3*n));
        
        int input;
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                cin >> input; v[i][j] = input;
            }
        }
        
        v = rotate90degree(v); // 90
        new_v = save(v,new_v,0);
        v = rotate90degree(v); // 180
        new_v = save(v,new_v,n);
        v = rotate90degree(v); // 270
        new_v = save(v,new_v,2*n);
        
        cout << "#" << t << '\n';
        for(int i=0; i<n; i++){
            output(new_v,i,0,n);
            output(new_v,i,n,2*n);
            output(new_v,i,2*n,3*n);
            cout << '\n';
        }
    }
}
