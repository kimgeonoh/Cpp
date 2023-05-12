#include<bits/stdc++.h>

using namespace std;

int m,n;
bool blocked[102][102];
int ans;

void dfs(int r,int c,int ops) {
    if(ops==0){
        if(blocked[r][c+1]){
            
            if(blocked[r+1][c]) return;
            
            ans++;
            blocked[r+1][c]=true;
            dfs(r+1,c,ops+1);
        }
        else{
            blocked[r][c+1]=true;
            dfs(r,c+1,ops);
        }       
    }
    
    else if(ops==1){
        if(blocked[r+1][c]){

            if(blocked[r][c-1]) return;
            
            ans++;
            blocked[r][c-1]=true;
            dfs(r,c-1,ops+1);

        }
        else{
            blocked[r+1][c]=true;
            dfs(r+1,c,ops);
        }
    }
    
    else if(ops==2){
        if(blocked[r][c-1]){
            if(blocked[r-1][c]) return;
            
            ans++;
            blocked[r-1][c]=true;
            dfs(r-1,c,ops+1);

        }
        else{
            blocked[r][c-1]=true;
            dfs(r,c-1,ops);
        }
    }
    else{
        if(blocked[r-1][c]){
            if(blocked[r][c+1]) return;
            
            ans++;
            blocked[r][c+1]=true;
            dfs(r,c+1,0);

        }
        else{
            blocked[r-1][c]=true;
            dfs(r-1,c,ops);
        }
    }
}


int main() {
    cin>>m>>n;
    
    memset(blocked,true,sizeof(blocked));
    
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            blocked[i][j]=false;
        }
    }
    blocked[1][1]=true;
    
    dfs(1,1,0);
    
    cout<<ans<<'\n';
}
