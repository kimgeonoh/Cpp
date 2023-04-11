// https://www.acmicpc.net/problem/3613

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool IsError(string s) {
	if (s.find('_') == string::npos) return isupper(s[0]); // 자바일때 앞에 대소문자로 정상,오류 구분
	
	else {                                                 // cpp인데 ('_'가 있을때)
		if (s[0] == '_' || s.back() == '_') return 1;      // 앞뒤에 '_' 가 있을 때 오류
		for (auto& i : s) if (isupper(i)) return 1;        // 대문자잇을때 오류
		return s.find("__") != string::npos;               // 연속된 '_'가 있을 때 오류
	}
}

string JavaToCpp(string s) {
	string ret;
	for (int i = 0; i < s.size();) {
		ret.push_back(tolower(s[i++]));
		while (i < s.size() && islower(s[i]))
			ret.push_back(tolower(s[i++]));
		ret.push_back('_');
	}
	ret.pop_back();
	return ret;
}

string CppToJava(string s) {
	string ret;
	for (int i = 0; i < s.size(); i++) {
		ret.push_back(toupper(s[i++]));
		while (i < s.size() && s[i] != '_')
			ret.push_back(s[i++]);
	}
	ret[0] = tolower(ret[0]);
	return ret;
}

int main() {
	string s; cin >> s;
	if (IsError(s)) cout << "Error!";               // 오류
	else {                                          // 정상
		bool flag = s.find('_') == string::npos;    // '_' 여부로 cpp, java 구분
		cout << (flag ? JavaToCpp : CppToJava)(s);
	}
}
