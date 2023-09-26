#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(int a, int b){
    string as = to_string(a); string bs = to_string(b);
    int an = as.size(); int bn = bs.size();
    
    if(an == bn){ // 자리수가 같다면
        for(int i=0; i<an; i++){ // 앞부터 큰 수가 리턴된다. 즉, 내림차순
            if(as[i] > bs[i]) return true;
            else if(as[i] < bs[i]) return false;
        }
    }
    else if(an < bn) {
        int j = 0;
        for(int i=0; i<bn; i++){
            if( i == an ) j = 0;  
            
            if(as[j] > bs[i]) return true;
            else if(as[j] < bs[i]) return false;
            
            j++;
        }
    }
    else { // an > bn
        int j = 0;
        for(int i=0; i<an; i++){
            if( i == bn ) j = 0;  
            
            if(as[i] > bs[j]) return true;
            else if(as[i] < bs[j]) return false;
            
            j++;
        }
    }
}

string solution(vector<int> numbers) {
    string answer = "";
    sort(numbers.begin(), numbers.end(), cmp);
    for(int number : numbers) answer = answer + to_string(number);
    if(answer[0] == '0') answer = "0";
    return answer;
}
