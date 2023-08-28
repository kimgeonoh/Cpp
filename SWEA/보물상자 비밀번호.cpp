#include<iostream>
#include<string>
#include<set>
using namespace std;
/*
5
12 10
1B3B3B81F75E
16 2
F53586D76286B2D8
20 14
88F611AE414A751A767B
24 16
044D3EBA6A647B2567A91D0E
28 11
8E0B7DD258D4122317E3ADBFEA99
*/
int N, K;
string numbers;

void init() {
    N = K = 0;
    numbers = "";
}

void input() {
    cin >> N >> K;
    cin >> numbers;
    numbers += numbers; // rotation처리
}

int Hex2Dec(string number) {
    // 16진수 -> 10진수로
    int ret = 0; // 10진수 수
    for (char ch : number) { // <- number에 있는 data들을 하나씩 ch라는 이름으로 복사
        int num;
        if ('0' <= ch && ch <= '9')
            num = ch - '0';
        else if ('A' <= ch && ch <= 'Z')
            num = ch - 'A' + 10; //-'A' : 0~25 index같은 수, +10 : A가 10부터 시작
        ret *= 16; // 자릿수 올리기(일의 자리 확보)
        ret += num; // 이번에 만든 수를 추가
    }
    return ret;
}

int solution() {
    set<int> s; // 오름차순
    for (int st = 0; st < N; st++) {
        //string temp = "";
        //for (int i = 0; i < N / 4; i++)
        //    temp += numbers[st + i];
        string temp = numbers.substr(st, N / 4); // 한 변을 이루고 있는 수
        int num = Hex2Dec(temp); // 16진수 -> 10진수 변환
        
        s.insert(num); // 중복없이 정렬된 모양
    }
    
    auto it = s.end(); // 맨 뒤에서부터 찾아가기
    for (int i = 0; i < K; i++) // K번째 큰 수 찾기
        it--;
    return *it;
}

int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        init(); // <- 
        input();
        int ans = solution();
        cout << "#" << tc << " " << ans << "\n";
    }
}
