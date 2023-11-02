#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <queue>

using namespace std;

struct info {
	int cnt; // 투표수
	string name; // 사전 순 정렬

	bool operator<(const info& left) const {
		if (cnt != left.cnt) return cnt > left.cnt; // 오름차순 
		return name.compare(left.name); // 사전순
	}
};

vector<string> votes = { "AAA", "BBB", "BBB", "BBB", "CCC", "BBB", "AAA" }; // "AAA","BBB","BBB","BBB","CCC","BBB","AAA"
map<string, int> candidates;
priority_queue<info> pq;
string answer;
int cnt = 0, k = 3;

int main() {
	// 입력
	// 보트에서 하나 꺼내
	// info 하나 만들어
	// 우선순위1.투표가장 적게 받은 사람이 탈락
	// 우선순위2.사전순

	for (auto v : votes) {
		candidates[v]++;
	}
	for (auto it = candidates.begin(); it != candidates.end(); it++) { 
		string name = it->first;
		int vote = it->second;
		pq.push({ vote,name });
	}

	// 탈락할때 표들의 합 
	// "CCC" 1표
	// "AAA" 2표

	while (!pq.empty()) {
		if (cnt >= k) break;

		info now = pq.top();
		pq.pop();

		answer = now.name;

		cnt += now.cnt;
	}

	// 탈락 끝
	// "BBB"

	// answer: "AAA"
	cout << answer << '\n';
}
