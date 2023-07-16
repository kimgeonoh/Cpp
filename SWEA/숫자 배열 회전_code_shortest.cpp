#include<iostream>

using namespace std;

int num[8][8];

int main(){
    int tc;
    cin >> tc;
    for (int t = 0; t < tc; t++) {
        int a;
        cin >> a;
        for (int i = 0; i < a; i++) 
            for (int j = 0; j < a; j++) 
                cin >> num[i][j];
        //입력끝
        int b = a - 1;
      
        cout << '#' << t + 1 << '\n';
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < a; j++) cout << num[b-j][i];
            cout << ' ';
            for (int j = 0; j < a; j++) cout << num[b - i][b-j];
            cout << ' ';
            for (int j = 0; j < a; j++) cout << num[j][b-i];
            cout << '\n';
        }
    }
    return 0;
}
