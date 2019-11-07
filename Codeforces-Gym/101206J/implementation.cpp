#include<bits/stdc++.h>
using namespace std;

string arr[6][30];
unordered_map<string, int> mp;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
		
	int caseNum; cin >> caseNum;
	for (int t = 1; t <= caseNum; t++) {
		int num; string str; cin >> num >> str;
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 20; j++)
				cin >> arr[i][j];
		mp.clear(); int rnk = 1;
		for (int j = 0; j < 20; j++)
			for (int i = 0; i < 5; i++)
				if (mp.find(arr[i][j]) == mp.end())
					mp[arr[i][j]] = rnk++;
		
		rnk = 1;
		for (int j = 0; j < 20; j++)
			cin >> arr[5][j];
		
		cout << "Case #" << t << ": ";
		int ans = -1;
		for (int y = 0; y <= num && ans == -1; y++) {
			int x = num - y;
			// Got the slot from regionals
			if (mp.find(str) != mp.end() && mp[str] <= x)
				continue;
			// Got the slot from EC
			int ecRank = 1, j;
			for (j = 0; j < 20 && arr[5][j] != str; j++) {
				if (mp.find(arr[5][j]) != mp.end() && mp[arr[5][j]] <= x)
					continue;
				ecRank++;
			}
			if (arr[5][j] == str && ecRank <= y)
				continue;
			ans = y;
		}
		
		if (ans == -1)
			cout << "ADVANCED!\n";
		else
			cout << ans << '\n';
	}
	
	return 0;
}