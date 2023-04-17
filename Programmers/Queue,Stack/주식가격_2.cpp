#include <string>
#include <vector>

using namespace std;

int arr[100000];

vector<int> solution(vector<int> prices) {
    vector<int> answer;
    int n = prices.size();
    
    for(int i = 0; i<n-1; i++){
        int j = 0;
        for(j = i+1; j<n; j++){
            if(prices[i] > prices[j]){ // 작은 수가 나왔을 경우
                j++;
                break;
            }
        }
        answer.push_back(j-i-1);
    }
    
    answer.push_back(0); // 마지막 예외 처리
    return answer;
}
