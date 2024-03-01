struct Node {
    int id; // 현재 정점의 ID
    int v; // 해당 ID의 Version
    Node* nxt; // 삭제를 하지 않기 때문에 prev 를 기억하지 않아도 된다.
    Node() {}
    Node(int id, int v) :id(id), v(v), nxt(nullptr) {}
    Node(int id, int v, Node* nxt) : id(id), v(v), nxt(nxt) {}
}node[500001]; // 미리 많이 만들어둔다
int cnt; // 50만개 중 몇개를 가져왔는가
int version[100001], num[100001]; // ID의 최신버전 기록, ID가 i인 사람이 속한 팀의 번호
 
Node* getNewNode(int id, Node* nxt = nullptr) { // 미리 만들어둔 node 주소를 가져온다
    Node* ret = &node[cnt++];
    ret->id = id;
    ret->nxt = nxt;
    ret->v = ++version[id];
    return ret;
}
 
struct Team {
    Node* head[6];
    Node* tail[6];
}t[6]; // t[i]: i 번팀의 n점은 head[n] ~ tail[n] 까지 병사가 존재한다
 
void init()
{
    cnt = 0;
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 5; j++) {
            t[i].tail[j] = t[i].head[j] = getNewNode(0); // dummy node
        }
    }
 
    for (int i = 0; i <= 100000; i++) {
        version[i] = 0;
        num[i] = 0;
    }
}
 
void hire(int mID, int mTeam, int mScore)
{
    Node* newNode = getNewNode(mID); // 생성
    t[mTeam].tail[mScore]->nxt = newNode; // tail 에 생성된 newNode 추가
    t[mTeam].tail[mScore] = newNode;     // tail update
    num[mID] = mTeam; // 어느 팀에 속해있는가 기록
}
 
void fire(int mID)
{
    version[mID] = -1; // 다시 고용되는 경우는 케이스 내에서 제외되기 때문에 예외가 없다
}
 
void updateSoldier(int mID, int mScore)
{
    hire(mID, num[mID], mScore); // linked list를 삭제하는 연산을 하지않고 새로운 병사를 version up 하여 update 한다.
}
 
void updateTeam(int mTeam, int mChangeScore)
{
    if (mChangeScore < 0) { // 음수로 업데이트
        // 
        for (int j = 1; j <= 5; j++) {
            int k = j + mChangeScore;
            if (k < 1) k = 1;
            if (k > 5) k = 5;
            if (j == k) continue; // 이동시킬 필요가 없는 점수
 
            // j -> k
            if (t[mTeam].head[j]->nxt == nullptr) continue;
            t[mTeam].tail[k]->nxt = t[mTeam].head[j]->nxt; // k의 tail을 j의 header에 연결한다. O(1)
            t[mTeam].tail[k] = t[mTeam].tail[j]; // tail update
            t[mTeam].head[j]->nxt = nullptr; // j inital
            t[mTeam].tail[j] = t[mTeam].head[j];
        }
    }
    if (mChangeScore > 0) { // 양수로 업데이트
        for (int j = 5; j >= 1; j--) { // 모두 같은 점수로 합쳐지는 것을 방지
            int k = j + mChangeScore;
            if (k < 1) k = 1;
            if (k > 5) k = 5;
            if (j == k) continue;

            
            if (t[mTeam].head[j]->nxt == nullptr) continue;
            t[mTeam].tail[k]->nxt = t[mTeam].head[j]->nxt;
            t[mTeam].tail[k] = t[mTeam].tail[j];
            t[mTeam].head[j]->nxt = nullptr;
            t[mTeam].tail[j] = t[mTeam].head[j];
        }
    }
}
 
int bestSoldier(int mTeam)
{
    for (int j = 5; j >= 1; j--) { // 높은 점수순으로 탐색
        Node* node = t[mTeam].head[j]->nxt;
        if (node == nullptr) continue;
 
        int ans = 0;
        while (node) {
            if (node->v == version[node->id]) { // 최신화된(유의미한) 노드인가
                ans = ans < node->id ? node->id : ans; // 높은 id 갱신
            }
            node = node->nxt;
        }
        if (ans != 0) return ans;
    }
    return 0;
}
