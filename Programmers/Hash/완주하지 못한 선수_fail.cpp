// memory 초과

#include <string>
#include <vector>
#include <set>

using namespace std;

string solution(vector<string> participant, vector<string> completion) {
    string answer = "";
    set<string> s;  
    for(auto v : participant) s.insert(v);
    for(auto v : completion) s.erase(v);
    
    auto it = s.begin();
    answer = *it;
    
    return answer;
}
