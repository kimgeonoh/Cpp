#include <string>

using namespace std;

string solution(string number, int k) {
    string answer;
    int idx = -1;
    
    for(int i=0; i<number.size()-k; i++){ // answer에 넣어야하는 수, number.size()-k 개
        char maxV = ' ';
        for(int j=idx+1; j<=k+i; j++){
            if(maxV < number[j]){
                maxV = number[j];
                idx = j;
            }
        }
        answer += maxV;
    }
	return answer;
}
