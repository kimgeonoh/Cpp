#include <bits/stdc++.h>

using namespace std;

int n,m;
vector<int> v[100001];
int s,t;
int visit[100001], visit2[100001];

void comm(int s, int t){
    queue<int> q;
    q.push(s);
    
    while(1){
        int now = q.back();
        visit[now]++;
        q.pop();
        if(visit[t]==2) break;
        for(int i=0; i<v[now].size(); i++){
            q.push(v[now][i]);
        }
    }
    
    queue<int> q2;
    q2.push(t);
    
    while(1){
        int now2 = q2.back();
        visit2[now2]++;
        q2.pop();
        if(visit2[s]==2) break;
        for(int i=0; i<v[now2].size(); i++){
            q2.push(v[now2][i]);
        }
    }

	int cnt = 0;
    
    for(int i=1; i<100001; i++){
        if(visit[i]&&visit2[i]){
            cnt++;
        }
    }
    
    cout << cnt-2 << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n >> m;
    
    for(int i=0; i<m; i++){
        int a,b; cin >> a >> b;
        v[a].push_back(b);
    }
    
    cin >> s >> t;
    
    comm(s,t);
}
