// 배열 넘기기

#include <bits/stdc++.h>

using namespace std;

int T, arr1[20], arr2[20];

int calculator(int arr1[], int arr2[], int smaller, int bigger){
    int result = -2e9;
    int move = bigger - smaller + 1, repeat = bigger - smaller;
    
    for(int i=0; i<move; i++){
        int temp=0;
        for(int rep=0; rep<smaller; rep++) {
            temp += arr1[rep] * arr2[rep+i];
        }
        result = max(result, temp);
    }

    return result;
}

int main() {
    cin >> T;
    for(int t=1; t<=T; t++){
        int N,M; cin >> N >> M;
        int MAX = -2e9;

        for(int i=0; i<N; i++) cin >> arr1[i]; // input
        for(int i=0; i<M; i++) cin >> arr2[i];
        
        if(N<M) MAX = calculator(arr1, arr2, N, M);
        else if(N>M) MAX = max(calculator(arr2, arr1, M, N), MAX);
        else {  // N=M 일때
            int temp = 0;
            for(int i=0; i<N; i++) temp += arr1[i] * arr2[i];
            MAX = max(temp, MAX);
        }
        
        cout << '#' << t << ' ' << MAX << '\n';
    }
}
