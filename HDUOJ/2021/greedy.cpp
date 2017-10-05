#include <iostream>
#include <cstdio>
using namespace std;

int getAns(int x)
{
	int ans = 0;
	ans += x / 100;
	ans += (x % 100) / 50;
	ans += (x % 50) / 10;
	ans += (x % 10) / 5;
	ans += (x % 5) / 2;
	if (x % 5 % 2 == 1)
		ans++;
	return ans;
}

int main()
{
	ios::sync_with_stdio(false);
	int n;
	while (cin >> n)
	{
		int ans = 0;
		if (n == 0)
			break;
		for (int i = 0; i < n; i++)
		{
			int tmp;
			cin >> tmp;
			ans += getAns(tmp);
		}
		cout << ans << endl;
	}		
	return 0;
}

