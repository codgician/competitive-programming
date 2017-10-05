#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;

int arr[10010];

bool cmpRule(int a, int b)
{
	return abs(a) > abs(b);
}

int main()
{
	ios::sync_with_stdio(false);
	int num;
	while (cin >> num)
	{
		if (num == 0)
			break;

		for (int i = 0; i < num; i++)
			cin >> arr[i];

		sort(arr, arr + num, cmpRule);

		for (int i = 0; i < num; i++)
		{
			cout << arr[i];
			if (i == num - 1)
				cout << endl;
			else
				cout << " ";
		}
	}
	return 0;
}

