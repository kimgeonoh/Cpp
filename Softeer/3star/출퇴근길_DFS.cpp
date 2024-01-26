#include <bits/stdc++.h>

using namespace std;

int n,m;
vector<int> adj[100001];
vector<int> adjR[100001];
int s,t;

void dfs(int now, vector<int> adj[100001], int visit[100001]){
    if(visit[now]==1) return;
    visit[now] = 1;
    for(int neighbor = 0; neighbor<adj[now].size(); neighbor++){
        dfs(adj[now][neighbor], adj, visit);
    }
    return;
}

int main() {
    cin >> n >> m;
    for(int i=0; i<m; i++){
        int x,y; cin >> x >> y;
        adj[x].push_back(y);
        adjR[y].push_back(x);
    }
    cin >> s >> t;
    
    int fromS[100001]{};
    fromS[t]=1;
    dfs(s, adj, fromS);
    
    int fromT[100001]{};
    fromT[s]=1;    
    dfs(t, adj, fromT);
    
    int toS[100001]{};
    dfs(s, adjR, toS);
    
    int toT[100001]{};
    dfs(t, adj, toT);
    
    int cnt = 0;
    /*for(int i=0; i<n; i++){
        if(fromS[i]&&fromT[i]&&toS[i]&&toT[i]) cnt++;
    }
    cout << cnt - 2 << '\n' ;*/
    
    for(int i=1; i<=n; i++){
        cout << fromS[i] << ' ' << fromT[i] << ' ' << toS[i] << ' ' << toT[i] << '\n';
    }
}
