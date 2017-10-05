#include <iostream>
#include <cstdio>
#include <climits>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	int n, m;
	while (cin >> n >> m)
	{
		if (n == 0 && m == 0)
			break;
		int prev = INT_MIN, next;
		bool flag = false;
		for (int i = 0; i < n; i++)
		{
			cin >> next;
			if (!flag && m > prev && m <= next)
			{
				cout << m << " ";
				flag = true;
			}
			prev = next;
			if (i == n - 1)
				cout << prev;
			else
				cout << prev << " ";
		}
		if (!flag)
			cout << m;
		cout << endl;
	}
	return 0;
}

