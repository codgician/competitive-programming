#include <iostream>
#include <cstdio>
using namespace std;

int cow[10010];

int main()
{
	ios::sync_with_stdio(false);
	int n;
	while (cin >> n)
	{
		if (n == 0)
			break;
		cow[0] = 1;
		cow[1] = 2;
		cow[2] = 3;
		cow[3] = 4;
		for (int i = 4; i < n; i++)
		{
			cow[i] = cow[i - 1] + cow[i - 3];
		}
		cout << cow[n - 1] << endl;
	}
	return 0;
}

