#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	int caseNum;
	cin >> caseNum;
	for (int t = 0; t < caseNum; t++)
	{
		string str;
		int ans = 0;
		cin >> str;
		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] - '0' >= 0 && str[i] - '0' <= 9)
				ans++;
		}
		cout << ans << endl;
	}
	return 0;
}

