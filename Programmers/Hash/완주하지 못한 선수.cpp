#include <string>
#include <vector>
#include <map>

using namespace std;

string solution(vector<string> participant, vector<string> completion) {
    string answer = "";
    
    map<string,int> m;
    for(auto v : participant) m[v] += 1;
    for(auto v : completion) m[v] -= 1;
    for(auto v : participant) {
        if(m[v] > 0 ) answer = v;
    }
    
    return answer;
}
