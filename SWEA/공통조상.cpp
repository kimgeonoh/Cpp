// https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV15PTkqAPYCFAYD

#include <iostream>
#include <vector>

using namespace std;

// 일반적인 트리 구현 방법
struct Node { // 각 정점마다 부모가 어느 정점인지, 자식의 정점을 기록한다
    vector<int> children;
    int parents;

    Node() : parents(0) {} // 아래와 같은 문법. 구조체의 생성자

    /*Node() {
        parents = 0;
    }*/
};

int ans, N, M, A, B;
Node* nodes;
vector<int> ancestorA, ancestorB;

void traverse(int idx, vector<int>& ancestor) {
    int parent = nodes[idx].parents;
    if (parent != 0) { // 부모가 존재한다면
        traverse(parent, ancestor); // 부모로 올라가기
    }
    ancestor.push_back(idx); // Root 부터 저장
}

int dfs(int idx) { // idx로 부터 모든 자식들을 불러 서브트리의 깊이를 구한다.
    int res = 1; // 나 자신의 depth
    for (int child : nodes[idx].children) { 
        res += dfs(child);
    }
    return res;
}

int main() {
    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        cin >> N >> M >> A >> B;
        nodes = new Node[N + 1];
        ancestorA.clear();
        ancestorB.clear();

        for (int i = 0; i < N + 1; i++) {
            nodes[i] = Node();
        }
        for (int i = 0; i < M; i++) {
            int p, c;
            cin >> p >> c;
            nodes[p].children.push_back(c);
            nodes[c].parents = p;
        }

        traverse(A, ancestorA); // A의 조상들을 모두 찾기
        traverse(B, ancestorB); // B "

        for (int i = 0; i < N; i++) {
            if (ancestorA[i] != ancestorB[i]) break;
            ans = ancestorA[i]; // LCA 
        }

        cout << "#" << t << " " << ans << " " << dfs(ans) << endl;
        
        delete[] nodes;
    }

    return 0;
}
