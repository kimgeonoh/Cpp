#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

const int NODE_MAX = 5000;

struct Node {
    int data;
    Node* next;

    Node(int data) : data(data), next(nullptr) {}
};

class LinkedList {
    Node* head; 
    Node* tail; // option, A 연산을 위함. 마지막 노드에 추가를 빠르게 하기 위함 
    vector<Node*> nodeArr; // new 연산자를 최대한 적게 사용하기 위함, memory pool
    int nodeCnt;

public:
    LinkedList() : head(nullptr), tail(nullptr), nodeCnt(0) {
        nodeArr.resize(NODE_MAX, nullptr);
    }

    Node* getNewNode(int data) {
        nodeArr[nodeCnt] = new Node(data);
        /* 다음 tc에서 사용해서 재활용할 수 있는 코드
        if (nodeArr[nodeCnt] == nullptr) {
            node[nodeCnt] = new Node(data);
        }
        else {
            nodeArr[nodeCnt].data = 0;
            nodeArr[nodeCnt].next = nullptr;
        }
        */
        return nodeArr[nodeCnt++];
    }

    void insert(int idx, const vector<int>& nums) { // dummy node 미사용
        // 원소추가
        int st = 0;
        if (idx == 0) {
            if (head != nullptr) {
                Node* newNode = getNewNode(nums[0]); // 새로운 head 생성
                newNode->next = head; // 헤드 link 연결
                head = newNode; // update
            }
            else {
                head = getNewNode(nums[0]); // 비어있는 linked list 추가
            }
            idx = 1;
            st = 1;
        }

        // 원하는 위치까지 이동
        Node* cur = head;
        for (int i = 1; i < idx; i++) {
            cur = cur->next;
        }

        // 값 추가
        for (int i = st; i < nums.size(); i++) {
            Node* newNode = getNewNode(nums[i]);
            // cur->nxt 에서
            // cur->NewNode->nxt 로 변경
            // 이때, 변경해주는 순서를 유의하자.
            // 70line, 71line을 바꿔서 쓰게되면 cur 노드가 변경되어서 무한히 자기자신으로 처리를 하게 된다.
            newNode->next = cur->next; // NewNode -> nxt 처리
            cur->next = newNode;       // cur -> NewNode 처리
            cur = newNode;             // cur 위치 update
        }

        // 마지막 원소를 추가한 경우 tail update
        if (cur->next == nullptr) {
            tail = cur;
        }
    }

    void remove(int idx, int cnt) {
        Node* cur = head;
        // 가장 앞을 처리할 경우 예외처리
        if (idx == 0) {
            for (int i = 0; i < cnt; i++) {
                cur = cur->next;
            }
            // 원하는 만큼 head를 넘어간다면 삭제해주는 처리와 같게된다.(좀비노드 생성)
            head = cur;
            return;
        }

        // 가장 앞이 아닐 경우
        // 삭제하고싶은 만큼 움직여 닻을 내린다
        for (int i = 1; i < idx; i++) {
            cur = cur->next;
        }
        Node* anchor = cur;

        // 닻을 내려서 멀리까지 던진다. 그 사이는 좀비노드가 된다.
        for (int i = 0; i < cnt; i++) {
            cur = cur->next;
        }
        anchor->next = cur->next;

        // 마지막 원소 수정 시 예외처리
        if (anchor->next == nullptr) {
            tail = anchor;
        }
    }

    void add(int data) {
        Node* cur = tail;
        Node* newNode = getNewNode(data);
        cur->next = newNode;
        tail = newNode; // tail update
    }

    void print() {
        int cnt = 10;
        Node* cur = head;
        while (cnt-- > 0) {
            cout << cur->data << " ";
            cur = cur->next;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T = 10;

    for (int t = 1; t <= T; t++) {
        LinkedList list;
        cout << "#" << t << " ";

        int N;
        cin >> N;

        vector<int> initArr(N);
        for (int i = 0; i < N; i++) {
            cin >> initArr[i];
        }
        list.insert(0, initArr);

        int M;
        cin >> M;

        for (int i = 0; i < M; i++) {
            char cmd;
            cin >> cmd;

            int x, y;
            vector<int> temp;
            switch (cmd) {
            case 'I':
                cin >> x >> y;
                temp = vector<int>(y);
                for (int j = 0; j < y; j++) {
                    cin >> temp[j];
                }
                list.insert(x, temp);
                break;
            case 'D':
                cin >> x >> y;
                list.remove(x, y);
                break;
            case 'A':
                cin >> y;
                for (int j = 0; j < y; j++) {
                    int data;
                    cin >> data;
                    list.add(data);
                }
                break;
            }
        }

        list.print();
        cout << "\n";
    }

    return 0;
}
