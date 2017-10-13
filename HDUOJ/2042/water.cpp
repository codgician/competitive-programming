#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	int caseNum;
	cin >> caseNum;
	for (int t = 0; t < caseNum; t++)
	{
		int num;
		cin >> num;
		int ans = 3;
		for (int i = num; i > 0; i--)
			ans = 2 * (ans - 1);
		cout << ans << endl;
	}
	return 0;
}

