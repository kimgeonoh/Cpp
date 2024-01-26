#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(){

	vector <pair<int,int>> v;
	int n,w,price=0; cin >> w >> n;

    for(int i=0;i<n;i++){
        int m,p; cin >> m >> p;
		v.push_back(pair<int,int>(p,m)); // 가격순 정렬을 위해 첫 파라미터는 가격
    }

    sort(v.begin(),v.end());
    
	for(int i=n-1 ;i>=0 && w>0 ;i--){
        int k = min(v[i].second,w);
        w -= k;
        price += k * v[i].first;
    }

	cout << price;
}
