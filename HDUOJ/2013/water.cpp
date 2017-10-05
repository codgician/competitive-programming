#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	int n;

	while(cin >> n)
	{
		int ans = 1;
		for (int i = 0; i < n - 1; i++)
		{
			ans = (ans + 1) * 2;
		}
		cout << ans << endl;
	}

	return 0;
}

