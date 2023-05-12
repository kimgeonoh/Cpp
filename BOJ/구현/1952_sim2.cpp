#include<bits/stdc++.h>

using namespace std;

int table[101][101];
int ans, cnt = 1;
int d,r,c;

int dr[4] = {0,1,0,-1}; //오 아 왼 위
int dc[4] = {1,0,-1,0};
 
int main(){
    
    int M, N;
    cin >> M >> N;
    
    table[r][c] = 1;
    while(1){
        
        if(cnt== M*N) break;
          
        int nr = r + dr[d];
        int nc = c + dc[d];
        
        //범위 넘어가거나 이미 map[i][j]==1 이면
        if(nr<0 || M-1<nr || nc<0 || N-1<nc || table[nr][nc]==1){
            ans++;
            if(d==3) d = 0;
            else d = d+1;
        }
        else{
            table[nr][nc] = 1;
            cnt += 1;
            r = nr;
            c = nc;
        }
    }
    
    cout << ans; 
}
