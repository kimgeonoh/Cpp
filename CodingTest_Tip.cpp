#include <iostream>

using namespace std;

// 1. 객체 지향의 중요성: 유지보수관리 용이함, 반복적인 작업 최소화, 로직 유지

class CLASSNAME{  // 가져야할 정보가 많을 경우 class를 이용하고 적은 경우 pair를 이용해도 좋다
  public:         // 나중에는 tuple도 배워보자
  int a,b,c
    CLASSNAME(int a, int b, int c){
      this->a = a;
      this->b = b;
      this->c = c;
    
      bool operator <(CLASSNAME &other){ // 정렬 기준으로 a의 오름차순
        return this->a < other.a;        
      }
  }
};

void function1(){
}

int function2(){
  return
}

vector<CLASSNAEE> class;
class.push_back(CLASSNAME(a,b,c));

// 2. 전체적인 flow를 종이로 적어 이해하고 직접 짜기 시작하며 중간중간 디버깅을 통해 정상적으로 돌아가는지 확인한다
//    절대 문제를 보자마자 바로 풀지 않는다. 안전하게 돌아가는길이 제일 빠른 길이다

// 3  push 개념, push는 특정 인덱스에 값을 넣는 함수가 아니다.

// 4. cin을 통해 입력을 받을 때 연속된 입력은 string, char로 받으면 배열로 나누어 입력받을 수 있다

// 5. 테스트케이스를 따라가며 히든 케이스를 생각한다

// 6. 시간제한이 1초일때
// N의 범위가 500인 경우 O(n3)
// N의 범위가 2000인 경우 O(n2)
// N의 범위가 100,00인 경우 O(n*log n)
// N의 범위가 10,000,000인 경우 O(n)

// 7. 조건의 범위에 따라 long long 선언

// 8. 순열조합 nCr 만들기: permutation 사용. 이는 algorithm 헤더에 존재한다
vector<bool> binary(n);
fill(binary.end()-3, binary.end(), true);
do{
  // binary가 특정 인덱스에서는 1이므로 이를 이용해 코드 진행
  ..
  } while(next_permutation(binary.begin(),binary.end()));
  

// 9. 2차원 벡터 만드는 방법 vector<vector<int>> v(n, vector<int>(m))
//    2차원 리스트 만드는 방법 vector<int> a[][]

// 10. 2차원 벡터 회전

vector<vector<int> > rotateMatrixBy90Degree(vector<vector<int> > a) {
    int n = a.size(); // 행 길이 계산
    int m = a[0].size(); // 열 길이 계산
    vector<vector<int> > result(n, vector<int>(m)); // 결과 리스트
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result[j][n - i - 1] = a[i][j];
        }
    }
    return result;
}

// 11. 경로탐색(최단거리, 시간), 네트워크(연결), 조합
//     해당 유형은 bfs / dfs  로 풀 수 있다

// 12. 삼항연산자는 리턴값을 반환한므로 cout 에서 1을 출력하고 싶다면 '1'이 아닌 1로 써야한다
cout << (s.empty() ? -1 : s.top()) << '\n';

// 13. stack<char> s

// 14. cout << fixed; cout.precision(n); 
//     fixed는 소수점 아래 이후부터 유효숫자를 세겠다
//     precision 유효 숫자 표기

// 15. swtich 문법
switch(variable){
    case '1' return;
    case '2' return;
}

// 16. isalpha
