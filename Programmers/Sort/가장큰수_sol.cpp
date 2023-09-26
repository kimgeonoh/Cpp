#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(int a, int b){
    string as = to_string(a); string bs = to_string(b);
    
    if ( (as + bs) > (bs + as)) return true;
    else return false;
}

string solution(vector<int> numbers) {
    string answer = "";
    sort(numbers.begin(), numbers.end(), cmp);
    for(int number : numbers) answer = answer + to_string(number);
    if(answer[0] == '0') answer = "0";
    return answer;
}
