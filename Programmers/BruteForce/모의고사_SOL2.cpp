#include <bits/stdc++.h>

using namespace std;
 
vector<int> solution(vector<int> answers) {
    vector<int> answer;
    //수포자가 찍는방식
    vector<vector<int>> math{ {1,2,3,4,5}, {2,1,2,3,2,4,2,5}, {3,3,1,1,2,2,4,4,5,5} };
    // 각자 몇개씩 맞췄는지 테스트
    vector<int> count = { 0, 0, 0 };
    for (int i = 0; i < answers.size(); i++) {
        // 정답을 각 번호와 비교하여 카운트 증가
        if (answers[i] == math[0][i % math[0].size()])    count[0]++;
        if (answers[i] == math[1][i % math[1].size()])    count[1]++;
        if (answers[i] == math[2][i % math[2].size()])    count[2]++;
    }
    //제일 높은 점수찾기
    int max = *max_element(count.begin(), count.end());
    //제일 높은 점수와 같은 사람 찾아서 정답에 추가, 앞에서 부터 추가했기때문에 정렬 필요없음
    for (int i = 0; i < 3; i++)
        if (max == count[i])    answer.push_back(i + 1);
    return answer;
}
