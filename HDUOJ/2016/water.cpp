#include <iostream>
#include <cstdio>
#include <climits>
using namespace std;

int arr[110];

int main()
{
	ios::sync_with_stdio(false);
	int num;
	while (cin >> num)
	{
		if (num == 0)
			break;
		int minn = INT_MAX;
		int loc;
		for (int i = 0; i < num; i++)
		{
			cin >> arr[i];
			if (arr[i] < minn)
			{
				minn = arr[i];
				loc = i;
			}
		}
		swap(arr[0], arr[loc]);
		for (int i = 0; i < num; i++)
		{
			cout << arr[i];
			if (i < num - 1)
				cout << " ";
			else
				cout << endl;
		}
	}
	return 0;
}

